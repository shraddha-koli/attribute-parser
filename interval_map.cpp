#include <map>
#include <limits>
#include <iostream>


template<typename K, typename V>
class interval_map {
	std::map<K,V> m_map;

public:
    // constructor associates whole range of K with val by inserting (K_min, val)
    // into the map
    interval_map( V const& val) {
        m_map.insert(m_map.end(),std::make_pair(std::numeric_limits<K>::lowest(),val));
    }

    // Assign value val to interval [keyBegin, keyEnd).
    // Overwrite previous values in this interval.
    // Conforming to the C++ Standard Library conventions, the interval
    // includes keyBegin, but excludes keyEnd.
    // If !( keyBegin < keyEnd ), this designates an empty interval,
    // and assign must do nothing.
    void assign( K const& keyBegin, K const& keyEnd, V const& val ) {
	if(keyBegin>keyEnd || keyBegin <= std::numeric_limits<K>::lowest()) return;
	m_map[keyBegin]=val;	
	m_map[keyEnd]=std::numeric_limits<V>::lowest();
	
	V endVal = val ;
	auto endit = m_map.find(keyEnd);
	
	if (prev(endit)->first == keyBegin){
	endVal = prev(prev(endit))->second;
	}
	else
	{
	endVal = prev(endit)->second;
	}
        m_map[keyEnd] = endVal;

	auto i  =  m_map.find(keyBegin);
	auto j = i;
	while(1){
		i = next(i);
		if (i == m_map.end()){break;}
		if(i->first == keyBegin){ break;}
		
		if (i->first < keyEnd && i->first > keyBegin){
		m_map.erase(i);
		continue;
		}	
		else if (i->second != val){ break;}
		else {m_map.erase(i);}
		
		}

	auto it = endit;
	auto endV = i->second;
	while(it != m_map.end()){
		i = next(it);
		if (i == m_map.end()){break;}
		if(i->first > keyEnd and i->second == endV){ m_map.erase(i);
		continue;
		;}
		if(i->first > keyEnd and i->second != endV){ break;}		
		}

		
	K temp = keyBegin;
	while(1){
		j = prev(j);
		if (j->second != val) break;		
		K newtemp = j->first;
		m_map.erase(temp);
		temp = newtemp;
		if (j == m_map.begin()) break;		
		}
		}


    // look-up of the value associated with key
    V const& operator[]( K const& key ) const {
	
	
        return ( --m_map.upper_bound(key) )->second;
    }
	
	void printMp(){
		for (auto i= m_map.begin(); i != m_map.end(); i++){
	
	std::cout<<i->first<<" "<<i->second<<std::endl;
	}

	}
};

int main(){
interval_map<signed int, int> mp('A');
mp.assign(-1, 5, 11);
mp.printMp();

mp.assign(1, 3, 12);
mp.printMp();

mp.assign(-1, 4, 13);
mp.printMp();
//mp.printVal(2);
return 0;
}

// Many solutions we receive are incorrect. Consider using a randomized test
// to discover the cases that your implementation does not handle correctly.
// We recommend to implement a test function that tests the functionality of
// the interval_map, for example using a map of unsigned int intervals to char.