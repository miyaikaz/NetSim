#include "network.h"
#include "random.h"
#include <algorithm>

#include <iostream>

void Network::resize(const size_t &n){
	std::vector<double> list(n);
	RandomNumbers rd;
	rd.normal(list, 0, 1);
	values = list;
}

bool Network::add_link(const size_t& a, const size_t& b){
	size_t n(values.size());
	std::vector<size_t> v (neighbors(a));
	bool neigh(false);
	for (unsigned int i(0); i < v.size(); ++i){
		if(i==b){neigh = true;}
	}
	if((not (a==b)) and (a < n) and (b < n) and (not neigh)){
		links.insert(std::make_pair(a, b));
		links.insert(std::make_pair(b, a));
		return true;
	}
	return false;
}

size_t Network::random_connect(const double& m){
	links.clear();
	RandomNumbers rd;
	unsigned int d(0);
	size_t p(0);
	for(unsigned int i(0); i<values.size();++i){
		d=rd.poisson(m);
		for(unsigned int j(0); j<d;++j){
			if(add_link(i,rd.uniform_double(0,(values.size()-1)))){
				++p;
			}
		}
	}
	return p;
}
 
size_t Network::set_values(const std::vector<double>& v){
	size_t s(values.size());
	size_t n(v.size());
	if(n<=s){
		for(unsigned int i(0); i<n; ++i){
			values[i]=v[i];
		}
		return n;
	}
	else if(n>s){
		for(unsigned int i=0; i<s; ++i){
			values[i]=v[i];
		}
		return s;
	}
	return 0;
}

size_t Network::size() const{
	return values.size();
}

size_t Network::degree(const size_t &_n) const{
	return links.count(_n);
}

double Network::value(const size_t &_n) const{
	return values[_n];
}

std::vector<double> Network::sorted_values() const{
	std::vector <double> v (values);
	std::sort(v.begin(), v.end(),std::greater<double>());
	return v;
}

std::vector<size_t> Network::neighbors(const size_t& a) const{
    std::vector<size_t> neigh;
    size_t b(a);
    
    auto ret(links.equal_range(b));
    for(auto it=ret.first; it!=ret.second; ++it){
		neigh.push_back(it->second);
	}
	return neigh;
}
