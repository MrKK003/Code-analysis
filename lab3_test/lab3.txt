
#include "scanner.hpp"

using namespace std;

bool isID(const string &str)
{
  if(isdigit(str[0]))
    return false;
  int counter = 0;
  if(str[0] == '_')
    counter++;

  for(; counter < str.size(); counter++)
    if(!(isalnum(str[counter])))
      return false;

  return true;
}

bool isComment(const string &str)
{
  return str == "//";
}


bool isDigits(const string &str)
{
  return all_of(str.begin(), str.end(), ::isdigit);
}


bool isString(const string &str)
{
    return str[0] == '"' && str[str.size()-1] == '"';
}

bool isSymbol(const string &str)
{
    return str[0] == '\'' && str[str.size()-1]== '\'';
}

bool isBool(const string &str)
{
  return str == "true" || str == "false";
}

bool isLiteral(const string &str)
{
  return isString(str) || isBool(str);
}

bool isKeyword(const string &str)
{
  const vector<string> keywords{"auto","break","case","const","continue","default",
      "do","else","enum","extern","for","goto","if","register","return","signed", "sizeof","static","struct","switch","typedef","union","unsigned","void","volatile","while", "false","true","cout","cin"};
  for(const auto& keyword : keywords)
    if (keyword == str)
      return true;

  return false;
}

bool isDataType (const string &str)
{
    const vector<string> data_types{"bool","string","char","int","double","long","float","short"};
    for(const auto& data_type : data_types)
      if (data_type == str)
        return true;

    return false;
}

bool isOperator(const string &str)
{
  const vector<string> operators{ "<", ">", "<=", ">=", "*", "+", "-", "/", "=", "-=", "*=", "+=", "/=", "++", "--", "==", "&&", "||", "%", "!=", "!", "&", "^", ">>", "<<", "|", "%=", "&=", "^=", "|=", "<<=", ">>=", "->"};
  for(const auto& op : operators)
    if (op == str)
      return true;

  return false;
}

bool isSeparator(const string &str)
{
    const vector<string> Separators{"{", "}", ",", "(", ")", ";", "[", "]", ":"};
  for(const auto& separate : Separators)
    if (separate == str)
      return true;

  return false;
}

bool isNotLegal(const string &str)
{
  return str == " " || str == "\n";
}

void printRoleOfToken(const string& token)
{
  if(isOperator(token))
    cout << token << " -> " << "Оператор" <<endl;
  else if(isSeparator(token))
    cout << token << " -> " << "Розділовий знак" <<endl;
  else if(isKeyword(token))
    cout << token << " -> " << "Зарезервоване слово" <<endl;
  else if(isDataType(token))
    cout << token << " -> " << "Тип змінної" <<endl;
  else if(isLiteral(token))
    cout << token << " -> " << "Рядкова константа" <<endl;
  else if(isSymbol(token))
    cout << token << " -> " << "Символьна константа" <<endl;
  else if(isID(token))
    cout << token << " -> " << "Ідентифікатор" <<endl;
    
  else if(isDigits(token))
    cout << token <<" -> "<< "Десяткове число" <<endl;
}

void lexicalAnalyze(const string &nameOfFile)
{
  char ch;
  string buffer;
  fstream file(nameOfFile, fstream::in);

  if (!file.is_open())
  {
    cout << "Error while opening the file\n";
    exit(0);
  }


  while (file >> noskipws >> ch)
  {
      

    if(isNotLegal(string(1, ch)))
    {
      if(!buffer.empty())
      {
        printRoleOfToken(buffer);
        buffer = "";
      }
      continue;
    }

    if(isOperator(string(1, ch)) && !isOperator(buffer))
    {
      if(!buffer.empty())
      {
        printRoleOfToken(buffer);
        buffer = "";
      }
    }

    if(!isOperator(string(1, ch)) && isOperator(buffer))
    {
      printRoleOfToken(buffer);
      buffer = "";
    }

    if(isSeparator(string(1, ch)))
    {
      if(!buffer.empty())
      {
        printRoleOfToken(buffer);
        buffer = "";
      }
      if(isSeparator(string(1, ch)))
      {
        printRoleOfToken(string(1, ch));
        continue;
      }
    }
      
    buffer += ch;
  }
  file.close();
}
