
#include <istream>
#include <map>
#include <set>
#include <regex>
#include <stdexcept>

namespace API
{
   struct Entry
   {
      std::string m_description;
      std::string m_value;
   };
   
   std::ostream& operator<<(std::ostream& os, Entry const& e)
   {  return os << "value: " << e.m_value << ", description: " << e.m_description; }
   
   std::ostream& operator<<(std::ostream& os, std::pair<std::string, Entry> const& tuple)
   {  return os << tuple.first << ": [" << tuple.second << "]"; }
   
   typedef std::map<std::string, Entry> EntryMapType;
   
   std::ostream& operator<<(std::ostream& os, EntryMapType const& map)
   {  
      for (auto tuple : map) { os << tuple << '\n'; }
      return os;
   }
   
   struct ColumnSeparator
   {
      ColumnSeparator(std::string::value_type separator) : m_separator(separator) {}
      operator std::string::value_type() const { return m_separator; }
      std::string::value_type m_separator;
   };
   
   struct Context
   {
      Context(std::istream& input, ColumnSeparator columnSeparator) : m_input(input), m_columnSeparator(columnSeparator), m_entryMap() {}

      EntryMapType getEntryMap() const
      {  return m_entryMap; }
      
      void addEntry(std::string key, Entry entry)
      {  m_entryMap.emplace(EntryMapType::value_type(key, entry)); }
      
      std::tuple<bool, std::string> getLine() 
      {
         std::string s;
         std::getline(m_input, s);
         return std::make_tuple(!m_input.eof() && m_input.good(), s);
      }
      
      std::string::value_type getColumnSeparator() const { return m_columnSeparator.m_separator; }
   private:
      std::istream& m_input;
      ColumnSeparator m_columnSeparator;
      EntryMapType m_entryMap;
   };
   
   struct Interpreter
   {
      virtual ~Interpreter() {}
      virtual Context& evaluate(Context& context) = 0;
   };
}

namespace Detail
{
   std::regex const outerSpaceAndTab("(^[\\s\\t]*)|([\\s\\t]*$)");
   
   template <typename... Ts>
   std::string format(const std::string &fmt, Ts... vs)
   {
       char b(0);
       auto const required(std::snprintf(&b, 0, fmt.c_str(), vs...) + 1);
       char bytes[required];
       std::snprintf(bytes, required, fmt.c_str(), vs...);
       return std::string(bytes);
   }
   
   struct KeyInterpreter : API::Interpreter
   {
      KeyInterpreter(std::vector<std::string> keyLines) : m_keyLines(keyLines), m_keys() {}
      
      virtual API::Context& evaluate(API::Context& context) override
      {  
         for (auto& line : m_keyLines)
         { 
            line = std::regex_replace(line, outerSpaceAndTab, "");
            if (!line.empty()) 
            {  m_keys.insert(line); }
         }
         if (m_keys.size() != 1)
         {  throw std::invalid_argument("Found no or multiple keys, expected exactly one"); }
         return context; 
      }
      
      std::string getKey() const { return *m_keys.begin(); }
      
   private:
      std::vector<std::string> m_keyLines;
      std::set<std::string> m_keys;
   };
   
   struct ValueInterpreter : API::Interpreter
   {
      ValueInterpreter(std::vector<std::string> valueLines) : m_valueLines(valueLines), m_values() {}
      
      virtual API::Context& evaluate(API::Context& context) override
      {  
         for (auto& line : m_valueLines)
         { 
            line = std::regex_replace(line, outerSpaceAndTab, "");
            if (!line.empty()) 
            {  m_values.insert(line); }
         }
         if (m_values.size() != 1)
         {  throw std::invalid_argument("Found no or multiple values, expected exactly one"); }
         return context; 
      }
      
      std::string getValue() const { return *m_values.begin(); }
      
   private:
      std::vector<std::string> m_valueLines;
      std::set<std::string> m_values;
   };
   
   struct DescriptionInterpreter : API::Interpreter
   {
      DescriptionInterpreter(std::vector<std::string> descriptionLines) : m_descriptionLines(descriptionLines), m_description() {}
      
      virtual API::Context& evaluate(API::Context& context) override
      { 
         std::ostringstream os;
         ///< Use boost::string::join, but here we don't the dependency to boost
         if (m_descriptionLines.empty()) 
         {  return context; }
         else
         if (m_descriptionLines.size() == 1)
         {  os << std::regex_replace(*m_descriptionLines.begin(), outerSpaceAndTab, ""); }
         else
         {
            std::for_each(m_descriptionLines.begin(), m_descriptionLines.end() - 1, [&](std::string const& line)
            {  os << std::regex_replace(line, outerSpaceAndTab, "") << ' '; });
            os << std::regex_replace(*m_descriptionLines.rbegin(), outerSpaceAndTab, "");
         }
         m_description = os.str();
         return context; 
      }
      
      std::string getDescription() const { return m_description; }
      
   private:
      std::vector<std::string> m_descriptionLines;
      std::string m_description;
   };
   
   struct BlockInterpreter : API::Interpreter
   {
      BlockInterpreter(std::vector<std::string> blockLines) : m_blockLines(blockLines) {}
      
      virtual API::Context& evaluate(API::Context& context) override
      {
         std::regex const columnBegin(format("[%c][^%c]+", context.getColumnSeparator(), context.getColumnSeparator()));
         std::regex const trim(format("(^[%c\\s\\t]*)|([%c\\s\\t]*$)", context.getColumnSeparator(), context.getColumnSeparator()));
         std::map<int, std::vector<std::string>> columnLines;
         for (auto line : m_blockLines) 
         {  
            std::smatch match;
            for (unsigned int column(0); std::regex_search(line, match, columnBegin); ++column)
            {
               columnLines[column].push_back(std::regex_replace(match.str(), trim, ""));
               line = match.suffix().str();
            }
         }
         KeyInterpreter key(std::move(columnLines[0]));
         key.evaluate(context);
         DescriptionInterpreter description(std::move(columnLines[1]));
         description.evaluate(context);
         ValueInterpreter value(std::move(columnLines[2]));
         value.evaluate(context);
         
         API::Entry entry;
         entry.m_value = value.getValue();
         entry.m_description = description.getDescription();
         context.addEntry(key.getKey(), std::move(entry));         
         return context;
      }
      
   private:
      std::vector<std::string> m_blockLines;
   };
}

namespace Concrete
{
   struct StreamInterpreter final : API::Interpreter
   {      
      virtual API::Context& evaluate(API::Context& context) override
      {
         std::regex const blockBegin(Detail::format("^[%c][\\s]*([^\\s\\t%c]+[\\s]*)+[%c].*", context.getColumnSeparator(), context.getColumnSeparator(), context.getColumnSeparator()));
         std::regex const comment(Detail::format("^[%c]([~]+[%c])+$", context.getColumnSeparator(), context.getColumnSeparator()));
         auto forEachLine([&](auto onBlockBegin, auto onNoMatch)
         {
            for (auto lineTuple(context.getLine()); std::get<0>(lineTuple); lineTuple = context.getLine())
            {
               auto const line(std::regex_replace(std::get<1>(lineTuple), Detail::outerSpaceAndTab, ""));
               if (std::regex_match(line, comment))
               {  continue; }
               if (std::regex_match(line, blockBegin))
               {  if (!onBlockBegin(line)) { break; } }
               else
               {  if (!onNoMatch(line)) { break; } }
            }
         });
         auto handleBlock([&](auto blockLines)
         {  
            auto block(std::make_unique<Detail::BlockInterpreter>(std::move(blockLines)));
            block->evaluate(context);
         });
         
         std::vector<std::string> blockLines;
         forEachLine([&](std::string const& line)
         { 
            blockLines.push_back(line);
            return false; 
         }, [](std::string const& line) 
         { 
            return true; 
         });
         forEachLine([&](std::string const& line)
         {
            handleBlock(std::move(blockLines));
            blockLines.push_back(line);
            return true;
         }, [&](std::string const& line)
         {
            blockLines.push_back(line);
            return true; 
         });
         if (!blockLines.empty())
         {  handleBlock(std::move(blockLines)); }
         
         return context;
      }
   };
}
