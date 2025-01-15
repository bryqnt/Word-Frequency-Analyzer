#ifndef WORD_FREQUENCY_HXX
#define WORD_FREQUENCY_HXX

///////////////////////// TO-DO (1) //////////////////////////////
  /// Include necessary header files
  /// Hint:  Include what you use, use what you include
  ///
  /// Do not put anything else in this section, i.e. comments, classes, functions, etc.  Only #include directives
#include <iostream>
#include <unordered_map>
#include <fstream>
#include <string>
#include <cstddef>
/////////////////////// END-TO-DO (1) ////////////////////////////







// unnamed, anonymous namespace providing non-member private working area
namespace
{
  std::string sanitize( std::string_view word )
  {
    constexpr char bad_char[] = " \t\r\n\b\v_-\"'(){}+/*,=.!?:;";                     // leading and trailing characters to be removed
    static std::locale locality{ "en_GB.UTF-8" };

    auto startIndex = word.find_first_not_of( bad_char );                             // start with the first non-bad character
    if( startIndex == std::string_view::npos ) startIndex = word.size();              // if the word contains only bad characters ...

    std::size_t count    = 0;                                                         // assume the word contains only bad characters ...
    auto        endIndex = word.find_last_not_of( bad_char );                         // end with the first non-bad character

    if( endIndex != std::string_view::npos ) count = endIndex - startIndex + 1;       // number of characters to use in results

    std::string result{ word.substr( startIndex, count ) };                           // strip the leading and trailing bad characters
    for( auto & c : result ) c = std::tolower( c, locality );                         // convert to lower case

    return result;                                                                    // result is moved optimized (copy elision) to the caller, std::move( result ) not required
  }
}  // unnamed, anonymous namespace







// Implement WordFrequency::WordFrequency( std::istream ) - See requirements
///////////////////////// TO-DO (2) //////////////////////////////
template<typename Hasher>
WordFrequency<Hasher>::WordFrequency(std::istream &iStream)
{
  std::string currentWord;
  while (iStream >> currentWord)
  {
    frequencyMap[sanitize(std::move(currentWord))]++;
  }
}
/////////////////////// END-TO-DO (2) ////////////////////////////







// Implement WordFrequency::numberOfWords() const - See requirements
///////////////////////// TO-DO (3) //////////////////////////////
template<typename Hasher>
std::size_t WordFrequency<Hasher>::numberOfWords() const
{
  return frequencyMap.size();
}
/////////////////////// END-TO-DO (3) ////////////////////////////







// Implement WordFrequency::wordCount( const std::string & ) const - See requirements
///////////////////////// TO-DO (4) //////////////////////////////
template<typename Hasher>
std::size_t WordFrequency<Hasher>::wordCount(const std::string_view word) const
{
    auto sanitizedWord = sanitize(word);  

    auto it = frequencyMap.find(sanitizedWord);  
    return (it != frequencyMap.end()) ? it->second : 0;  
}
/////////////////////// END-TO-DO (4) ////////////////////////////







// Implement WordFrequency::mostFrequentWord() const - See requirements
///////////////////////// TO-DO (5) //////////////////////////////
template<typename Hasher>

std::string WordFrequency<Hasher>::mostFrequentWord() const
{
  if (frequencyMap.empty()) return "";  

  auto it = frequencyMap.begin();  
  std::string mostFrequent = it->first;  
  std::size_t maxFrequentCount = it->second;  

  for (++it; it != frequencyMap.end(); ++it)  
  {
    if (it->second > maxFrequentCount)
    {
      mostFrequent = it->first;
      maxFrequentCount = it->second;
    }
  }
  return mostFrequent;
}
/////////////////////// END-TO-DO (5) ////////////////////////////







// Implement WordFrequency::maxBucketSize() const - See requirements
///////////////////////// TO-DO (6) //////////////////////////////
  /// Hint: see the unordered_map's bucket interface at https://en.cppreference.com/w/cpp/container/unordered_map

template<typename Hasher>
std::size_t WordFrequency<Hasher>::maxBucketSize() const
{
  if (frequencyMap.empty()) 
  {
    return 0;
  }

  std::size_t maxBucketSize = frequencyMap.bucket_size(0); 
  for (auto bucketIndex = 1U; bucketIndex < frequencyMap.bucket_count(); ++bucketIndex) 
  {
    std::size_t currentBucketSize = frequencyMap.bucket_size(bucketIndex);
    if (currentBucketSize > maxBucketSize)
    {
      maxBucketSize = currentBucketSize;
    }
  }
  return maxBucketSize;
}
/////////////////////// END-TO-DO (6) ////////////////////////////







// Implement WordFrequency::bucketSizeAverage() const - See requirements
///////////////////////// TO-DO (7) //////////////////////////////
template<typename Hasher>
double WordFrequency<Hasher>::bucketSizeAverage() const
{
  const std::size_t totalBuckets = frequencyMap.bucket_count();
  if (totalBuckets == 0)
  {
    return 0;
  }
  std::size_t totalSize = 0;
  for (std::size_t i = 0; i < totalBuckets; ++i)
  {
    totalSize += frequencyMap.bucket_size(i);
  }
   return static_cast<double>(totalSize) / static_cast<double>(totalBuckets);
}
/////////////////////// END-TO-DO (7) ////////////////////////////




#endif    // WORD_FREQUENCY_HXX
