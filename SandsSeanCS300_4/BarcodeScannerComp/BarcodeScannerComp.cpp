#include <time.h>	//	for timing
#include <fstream>	//	to read corpus, and write results
#include <string>	//	key and value type
#include <vector>	//	key container


#include "ArrayMap.h"	//map implementations
#include "BSTMap.h"	

int main()
{
	//array of sizes
	size_t sizes[] = { 1, 11, 101, 1001, 10001, 100001, 1000001 };

	clock_t t;

	//	for each size, create and fill array and bst implementations with that many values
	//	also fill a vector with ~100 evenly distributed keys
	//	then search for each value associated with a stored key, logging times in a .txt
	for (size_t s : sizes)
	{
		size_t dist = s / 100;	//	index distribution
		if (dist == 0) { dist = 1; }
		//initialize filestreams
		std::ifstream ifs("upc_corpus.txt");
		std::string ofn("test");
		ofn += std::to_string(s);
		ofn += ".txt";
		std::ofstream ofs(ofn);
		
		//initialize containers
		BSTMap<std::string, std::string> bbs;
		ArrayMap<std::string, std::string> bas(s);
		std::vector<std::pair<size_t,std::string>> keys;
		keys.reserve(s);
		
		//eat dummy line at top of corpus
		std::string firstline;
		std::getline(ifs, firstline);
		
		//fill containers, key vector
		for (size_t i = 0; i < s; ++i)
		{
			std::string k;
			std::string v;
			std::getline(ifs, k, ',');
			
			std::getline(ifs, v);
			
			try
			{
				bbs.insert(k, v);
				
			}
			catch (const int &e)
			{
				if (e == 1)	//	duplicate key
				{
					--i;	//	decrement count since nothing added, and %dist values could be missed otherwise
					continue;
				}
				else
				{
					throw e;
				}
			}
			if (i % dist == 0)
			{
				keys.push_back(std::make_pair(i,k));
			}
			bas.insert(k, v);
		}
		//	data header
		ofs << "index\tbst\tarr\tsec/" << CLOCKS_PER_SEC << std::endl;
		//search for keys, log times
		for (auto k: keys)
		{
			ofs << k.first << "\t";	//	print index
			t = clock();	//	start bst find clock
			auto v1 = bbs.find(k.second);	//	find value associated with key k
			t = clock() - t;	//	end bst find clock
			ofs << t << "\t";	//	print bst find clock to file
			t = clock();	//	start array find clock
			auto v2 = bas.find(k.second);	//	find value associated with key k
			t = clock() - t;	//	end array find clock
			ofs << t << std::endl;	//	print array find clock to file
		}
		
		ifs.close();
		ofs.close();
	}

	return 0;
}