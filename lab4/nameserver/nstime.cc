/*
 * nstime.cc: performs timing tests of the lookup() function in 
 * the three different name server implementations.
 */
#include "nameserverinterface.h"
#include "vectornameserver.h"
#include "mapnameserver.h"
#include "hashnameserver.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;
using namespace cpp_lab4;

/* dns_record is the type of a name/address pair */

typedef std::pair<HostName, IPAddress> dns_record;

/*
 * test() makes nbrSearches random searches in the name server ns for
 * names in the vector data, and computes the average search time
 * in milliseconds. Use rand() and srand() instead of random() and
 * srandom() if your system doesn't have the -om() functions.
 */
double measureTime(const NameServerInterface& ns,
                   const vector<dns_record>& data,
                   int nbrSearches, int randomSeed) {
    if (nbrSearches <= 0)
        return 0;

    /*
     * First, measure the administration time for the time measurement
     * loop.
     */
    srandom(randomSeed);
    int size = data.size();
    clock_t startTime = clock();
    for (int i = 0; i < nbrSearches; ++i) {
        int k = random() % size;        
        HostName name = data[k].first;
        IPAddress address = data[k].second;
        if (address == NON_EXISTING_ADDRESS)
            cerr << "Error: " << name << " not found" << endl;
        else if (address != data[k].second) 
            cerr << "Error: " << name << " returned wrong address, "
                 << address << endl;
    }
    clock_t elapsedTimeAdmin = clock() - startTime;
    
    /*
     * Then, the same loop but this time we really search in the
     * name server.
     */
    srandom(randomSeed);
    startTime = clock();
    for (int i = 0; i < nbrSearches; ++i) {
        int k = random() % size;        
        HostName name = data[k].first;
        IPAddress address = ns.lookup(name);
        if (address == NON_EXISTING_ADDRESS)
            cerr << "Error: " << name << " not found" << endl;
        else if (address != data[k].second) 
            cerr << "Error: " << name << " returned wrong address, "
                 << address << endl;
    }
    clock_t elapsedTimeSearch = clock() - startTime;

    double elapsedTime =
        static_cast<double> (elapsedTimeSearch - elapsedTimeAdmin) /
        CLOCKS_PER_SEC;
    return 1000 * elapsedTime / nbrSearches;
}

int main() {
    /*
     * The vector implementation.
     */
    VectorNameServer vns;

    /*
     * The map implementation.
     */
    MapNameServer mns;

    /*
     * The hash table implementation. The size of the hash table is
     * a parameter to the constructor.
     */
    HashNameServer hns(17441);
    
    ifstream in("nameserverdata.txt");
    if (! in) {
        cerr << "Could not open data file (nameserverdata.txt)" << endl;
        exit(1);
    }
    
    /*
     * data is a vector containing the name/address pairs. Used by the
     * measureTime() function.
     */
    vector<dns_record> data;
    
    /*
     * Read the input file, store in the data vector. At the same time,
     * insert the data into the name servers.
     */
    cout << "Reading ..." << flush;
    HostName name;
    IPAddress nbr;
    while (in >> name >> nbr) {
        dns_record rec(name, nbr);
        data.push_back(rec);
        vns.insert(name, nbr);
        mns.insert(name, nbr);
        hns.insert(name, nbr);
    }
    int size = data.size();
    cout << " read " << size << " words." << endl;
    
    /*
     * Read the number used to seed the random number generator. Use
     * any (preferably odd) number.
     */
    cout << "Random seed: " << flush;
    int seed;
    cin >> seed;

    /*
     * Measure the average search times for the three implementations.
     * Use a small (1000) value for the number of searches in the 
     * vector implementation, a larger (100 000) value for the other
     * implementations. What values that are reasonable depends on
     * your computer.
     */
    cout << "Test vector. Number of searches: ";
    int nbrSearches;
    cin >> nbrSearches;
    double avgTime = measureTime(vns, data, nbrSearches, seed);
    cout << "Average search time (ms): " << avgTime << endl;
    
    cout << "Test map. Number of searches: ";
    cin >> nbrSearches;
    avgTime = measureTime(mns, data, nbrSearches, seed);
    cout << "Average search time (ms): " << avgTime << endl;
   
    cout << "Test hash. Number of searches: ";
    cin >> nbrSearches;
    avgTime = measureTime(hns, data, nbrSearches, seed);
    cout << "Average search time (ms): " << avgTime << endl;
}
