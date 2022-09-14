#ifndef COMBINERS_H
#define COMBINERS_H

#include "searcheng.h"
#include <set>

/*** Define Derived WebPageSetCombiners (for AND, OR, DIFF) classes below ***/
class AndWebPageSetCombiner : public WebPageSetCombiner {
public:
	AndWebPageSetCombiner();
	virtual WebPageSet combine(const WebPageSet& setA, const WebPageSet& setB);
};

class OrWebPageSetCombiner : public WebPageSetCombiner {
public:
	OrWebPageSetCombiner();
	virtual WebPageSet combine(const WebPageSet& setA, const WebPageSet& setB);
};

class DiffWebPageSetCombiner : public WebPageSetCombiner {
public:
	DiffWebPageSetCombiner();
	virtual WebPageSet combine(const WebPageSet& setA, const WebPageSet& setB);
};




#endif