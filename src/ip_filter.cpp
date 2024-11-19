#include <cassert>
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;


using stringVector = vector<string>;
using vectorString = vector<stringVector>;
using sizeType = string::size_type;
// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]
stringVector split(const string &str, char d)
{
  stringVector r;

  sizeType start = 0;
  sizeType stop = str.find_first_of(d);
    while(stop != string::npos)
    {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}

bool Comp( const stringVector & sv1, 
           const stringVector & sv2 ) 
{
  bool res = false;
  size_t len1 = sv1.size();
  size_t len2 = sv2.size();
  len1 = min( len1, len2 );

  for ( size_t i = 0; i < len1; ++i ) {
    int vol1 = stoi( sv1[i] ); 
    int vol2 = stoi( sv2[i] );
    if( vol1 > vol2 ) {
      res = true;
      break;
    }
    else if ( vol1 < vol2 )
      break;
  }

  return res;
}

bool FindSubStr( const stringVector & str,
                 const stringVector & subStr )
{
  bool res = false;
  size_t len1 = str.size();
  size_t len2 = subStr.size();

  if ( len2 <= len1 ) {
    res = true;
    for ( size_t i = 0; i < len2; ++i ) {
      if ( str[i] != subStr[i] ) {
        res = false;
        break;
      }
    }
  }

  return res;
}

void Print( const vectorString & pool ) {
  std::cout << std::endl;

  for ( auto ip = pool.cbegin(); ip != pool.cend(); ++ip )
  {
    for ( auto ip_part = ip->cbegin(); ip_part != ip->cend(); ++ip_part )
    {
      if ( ip_part != ip->cbegin() )   
        std::cout << ".";      
      std::cout << *ip_part;
    }
    std::cout << std::endl;
  }
}

int main(int argc, char const *argv[])
{
    try
    {
      vectorString ip_pool, ip_filter1, ip_filter2, ip_filter_any;
      ifstream shows_file("ip_filter.tsv");
      stringVector filter1;
      filter1.emplace_back("1"); 
      stringVector filter2{ "46","70" };
      string filter_any("46");

        for(string line; std::getline(shows_file, line);)
        {
          stringVector v = split(line, '\t');
            ip_pool.push_back( split(v.at(0), '.') );
        }

        // TODO reverse lexicographically sort
        std::sort( ip_pool.begin(), ip_pool.end(), Comp );
        
        for( auto ip = ip_pool.cbegin(); ip != ip_pool.cend(); ++ip )
        {
            for( auto ip_part = ip->cbegin(); ip_part != ip->cend(); ++ip_part )
            {
                if ( ip_part != ip->cbegin() )               
                    std::cout << ".";
                std::cout << *ip_part;           
            }
            if ( ::FindSubStr(*ip, filter1) )
              ip_filter1.push_back( *ip );
            if ( ::FindSubStr(*ip, filter2) )
              ip_filter2.push_back( *ip );
            if ( find((*ip).begin(), (*ip).end(), filter_any) != (*ip).end() )
              ip_filter_any.push_back( *ip );
            std::cout << std::endl;
        }
        
        Print( ip_filter1 );
        Print( ip_filter2 );
        Print(ip_filter_any);
        // 222.173.235.246
        // 222.130.177.64
        // 222.82.198.61
        // ...
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // TODO filter by first byte and output
        // ip = filter(1)


        // 1.231.69.33
        // 1.87.203.225
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // TODO filter by first and second bytes and output
        // ip = filter(46, 70)

        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76

        // TODO filter by any byte and output
        // ip = filter_any(46)

        // 186.204.34.46
        // 186.46.222.194
        // 185.46.87.231
        // 185.46.86.132
        // 185.46.86.131
        // 185.46.86.131
        // 185.46.86.22
        // 185.46.85.204
        // 185.46.85.78
        // 68.46.218.208
        // 46.251.197.23
        // 46.223.254.56
        // 46.223.254.56
        // 46.182.19.219
        // 46.161.63.66
        // 46.161.61.51
        // 46.161.60.92
        // 46.161.60.35
        // 46.161.58.202
        // 46.161.56.241
        // 46.161.56.203
        // 46.161.56.174
        // 46.161.56.106
        // 46.161.56.106
        // 46.101.163.119
        // 46.101.127.145
        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76
        // 46.55.46.98
        // 46.49.43.85
        // 39.46.86.85
        // 5.189.203.46
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
