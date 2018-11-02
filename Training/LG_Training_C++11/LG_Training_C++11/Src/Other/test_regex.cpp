#include "test_regex.h"
#include <iostream>
#include <string>
#include <regex>
//Regular expressions are a standardized way to express patterns to be matched against sequences of characters.
//Regex operations
//regex_match
//regex_search
//regex_replace


void test_regex_match()
{
    std::string s("mm sub0a009ject(");
    std::smatch m;//typedef match_results<string::const_iterator> smatch;
    //Groups
    //std::regex e("(sub)([0-9][^0-9]?[0-9]+[^0-9]*).*");// sub followed by any character 
    //(...) 1 nhóm các ký tự
    //(sub)   tồn tại nhóm ký tự "sub"
    //([0-9][^0-9]?) tổn tại nhóm ký tự thỏa max regex bên trong dấu ()
    //Quantifiers
    //[0-9]   tồn tại 1 ký tự thỏa mãn [^0-9] (ký tự có giá trị từ 0 -> 9 such as 1,2,...,9) //[class]
    //[^0-9]  tồn tại 1 ký tự ngoài khoản 0 > 9 //[^class]
    //[^0-9]? tồn tại 0 hoặc 1 ký tự thỏa mã [^0-9]
    //[^0-9]+ tồn tại >= 1 ký tự thỏa mãn [^0-9]
    //[^0-9]* tồn tại >= 0 ký tự thỏa mãn [^0-9]
    //[^0-9]{2} tổn tại 2 ký tự thỏa mãn [^0-9]
    //[^0-9]{2,} tổn tại >= 2 ký tự thỏa mãn [^0-9]
    //[^0-9]{2,5} tổn tại >= 2 && <= 5 ký tự thỏa mãn [^0-9]
    //[abc1-5] matches either a, b or c, or a digit between 1 and 5.

    //target sequence: "mm sub0a009ject"
    //ký tự '(' được biểu diễn trong regex = \\(
    std::regex e("(?=mm)(^\\b.*)(\\b.*)(\\Ba[[:digit:]]{1})(0|9)(.*\\($)");
    //[mm sub0a009ject] [mm ] [sub0] [a0] [0] [09ject]
    //(^\\b.*) phía trước "\\b" là begining of target (non-word character), sau "\\b" là ký tự đầu tiên 'm'
    //Assertions
    //Assertions are conditions that do not consume characters in the target sequence: they do not describe a character, but a condition that must be fulfilled before or after a character.
    //^ : Beginning of line //Either it is the beginning of the target sequence, or follows a line terminator.
    //$ : End of line       //Either it is the end of the target sequence, or precedes a line terminator.
    //\b : Word boundary    //The previous character is a word character and the next is a non-word character (or vice-versa).
    //\B  : Not a word boundary //The previous and next characters are both word characters or both are non-word characters.
    //Alternatives
    //(?=subpattern) : Positive lookahead //The characters following the assertion must match subpattern, but no characters are consumed.
    //(?!subpattern) : Negative lookahead //The characters following the assertion must not match subpattern, but no characters are consumed.
    //Character classes
    //[:digit:] : alpha-numerical character
    //[[:alpha:]] : is a character class that matches any alphabetic character.
    //[abc[:digit:]] is a character class that matches a, b, c, or a digit.
    //[^[:space:]] is a character class that matches any character except a whitespace.

    std::string pattern("(bj)(.*)");
    //e.assign(pattern);//Assigns a new regular expression (pattern) to the object, overwriting any previous value.

    // regex_match function matches string a against regex b 
    if (std::regex_match(s, e))
        std::cout << "String 's' matches regular expression 'e' \n";

    std::regex_match(s, m, e);
    //std::regex_match(s.cbegin(), s.cend(), m, e);

    std::cout << "matches:" << std::endl;
    //for (std::smatch::iterator it = m.begin(); it != m.end(); ++it) {
    //    std::cout << *it << std::endl;
    //}

    for (unsigned i = 0; i<m.size(); ++i) {
        std::cout << "[" << m[i] << "]" << std::endl;
    }

    //------------------
    //matches:
    //sub
    //subject
    //ject
    //------------------
}

void test_regex_search()
{
    std::string s("this subject has a submarine as a doan2.nguyen@lge.com and  minhthedt@gmail.com hello");
    std::smatch m;
    //std::regex e("\\b(sub)([^ ]*)");   // matches words beginning by "sub"
    std::regex e("\\b[a-z0-9._%+-]+@[a-z0-9.-]+\\.[a-z]{2,4}\\b");
    //std::regex e("\\b[a-z0-9._%+-]+\\b");

    std::cout << "Target sequence: " << s << std::endl;
    std::cout << "Regular expression: /\\b(sub)([^ ]*)/" << std::endl;
    std::cout << "The following matches and submatches were found:" << std::endl;

    while (std::regex_search(s, m, e)) {
        for (auto x : m) std::cout <<"[" << x <<"]" << " ";
        std::cout << std::endl;
        s = m.suffix().str();
    }

    //------------------
    //Target sequence : this subject has a submarine as subsequence
    //Regular expression : / \b(sub)([^] * ) /
    //The following matches and submatches were found :
    //[subject] [sub] [ject]
    //[submarine] [sub] [marine]
    //[subsequence] [sub] [sequence]
    //------------------
    //[doan2.nguyen@lge.com]
    //[minhthedt@gmail.com]
}

void test_regex_replace()
{
    std::string s("there is a subsequence in the string\n");
    std::regex e("\\b(sub)([^ ]*)");   // matches words beginning by "sub"

                                       // using string/c-string (3) version:
    std::string new_str = std::regex_replace(s, e, "sub-$2");
    std::cout << new_str;

    // using range/c-string (6) version:
    std::string result;
    std::regex_replace(std::back_inserter(result), s.begin(), s.end(), e, "$2");
    std::cout << result;

    // with flags:
    std::cout << std::regex_replace(s, e, "$1 and $2", std::regex_constants::format_no_copy);
    std::cout << std::endl;

    //------------------
    //there is a sub - sequence in the string
    //there is a sequence in the string
    //sub and sequence
    //------------------
}

void test_regex_iterator()
{
    std::string s = "Some people, when confronted with a problem, think "
        "\"I know, I'll use regular expressions.\" "
        "Now they have two problems.";

    std::regex self_regex("REGULAR EXPRESSIONS",
        std::regex_constants::ECMAScript | std::regex_constants::icase);
    if (std::regex_search(s, self_regex)) {
        std::cout << "Text contains the phrase 'regular expressions'\n";
    }

    std::regex word_regex("(\\S+)");
    auto words_begin =
        std::sregex_iterator(s.begin(), s.end(), word_regex);
    auto words_end = std::sregex_iterator();

    std::cout << "Found "
        << std::distance(words_begin, words_end)
        << " words\n";

    const int N = 6;
    std::cout << "Words longer than " << N << " characters:\n";
    for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
        std::smatch match = *i;
        std::string match_str = match.str();
        if (match_str.size() > N) {
            std::cout << "  " << match_str << '\n';
        }
    }

    std::regex long_word_regex("(\\w{7,})");
    std::string new_s = std::regex_replace(s, long_word_regex, "[$&]");
    std::cout << new_s << '\n';
}

void test_regex()
{
    //test_regex_match();
    test_regex_search();
}