#ifndef NODE_HH
#define NODE_HH 1

/******************************************************************
** Node.hh
**
** Description of a node of the de Bruijn graph 
** 
**  Authors: Giuseppe Narzisi & Michael C. Schatz
**    Date: December 11, 2013
**
*******************************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <assert.h>
#include <unordered_set>

#include "Mer.hh"
#include "Ref.hh"
#include "Edge.hh"
#include "ContigLink.hh"
#include "ReadInfo.hh"
#include "ReadStart.hh"

using namespace std;

// Node_t
//////////////////////////////////////////////////////////////////////////

class Node_t
{
public:

	// members
	//////////////////////////////////////////////////////////////

	Mer_t nodeid_m;

	string str_m;
	float cov_m;
	bool isRef_m;
	bool isTumor_m;
	bool isNormal_m;
	bool isSource_m;
	bool isSink_m;
	bool dead_m;
	int  component_m;
	bool touchRef_m;
	int  onRefPath_m;
	int color;

	vector<int> cov_distr;
	vector<Edge_t> edges_m;
	unordered_set<ReadId_t> reads_m;
	vector<ReadStart_t> readstarts_m;
	ContigLinkMap_t contiglinks_m;
	ReadInfoList_t * readid2info;


	Node_t(Mer_t mer) 
		: nodeid_m(mer), 
		str_m(mer), 
		cov_m(0), 
		isRef_m(false),
		isTumor_m(false),
		isNormal_m(false),
		isSource_m(false),
		isSink_m(false),
		dead_m(false),
		component_m(0),
		touchRef_m(false),
		onRefPath_m(0),
		color(0)
		{ cov_distr.resize(str_m.size()); }

	friend ostream& operator<<(std::ostream& o, const Node_t & n) { return n.print(o); }
	friend ostream & operator<<(std::ostream & o, const Node_t * n) { return n->print(o); }

	bool isRef() const { return isRef_m; }
	bool isSource() const { return isSource_m; }
	bool isSink() const { return isSink_m; }
	bool isTumor() const { return isTumor_m; }
	bool isNormal() const { return isNormal_m; }
	bool isSpecial() const { return (isSink_m || isSource_m || isRef_m); }
	
	void setIsRef() { isRef_m = true; }
	void setIsSource() { isSource_m = true; }
	void setIsSink() { isSink_m = true; }
	void setIsTumor() { isTumor_m = true; }
	void setIsNormal() { isNormal_m = true; }
	
	void setRead2InfoList(ReadInfoList_t * list) { readid2info = list; }
	
	void setColor(int c) { color = c; }
	int getColor() { return color; }

	bool isTandem();
	void addEdge(Mer_t nodeid, Edgedir_t dir, ReadId_t readid);
	void updateEdge(const Mer_t & oldid, Edgedir_t olddir, const Mer_t & newid, Edgedir_t newdir);
	void removeEdge(const Mer_t & nodeid, Edgedir_t dir);
	int getBuddy(Ori_t dir);
	int markRef(Ref_t * ref, int K);
	int degree(Ori_t dir);
	ostream & print(ostream & out) const;
	int strlen() const;
	void addReadStart(ReadId_t readid, int nodeoffset, int trim5, Ori_t ori);
	void revreads();
	void sortReadStarts();
	void addContigLink(Mer_t contigid, ReadId_t rid);
	int cntReadCode(char code);
	void updateCovDistr(int c);
	void revCovDistr();
	int minCov();
	int readOverlaps(const Node_t & other);
};


#endif