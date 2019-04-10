/*
 * DratPrint.h
 *
 *  Created on: 10.04.2019
 *      Author: hartung
 */

#ifndef MTL_DRATPRINT_H_
#define MTL_DRATPRINT_H_

#include "core/SolverTypes.h"
#include <cstdio>
#include <string>

class DratPrint {
public:
	DratPrint(const std::string & proofFileName) :
			proof(fopen(proofFileName.c_str(), "wb")) {
	}

	~DratPrint() {
		fclose(proof);
	}

	template<typename VecType>
	void dumpAddClause(const VecType & c) {
		dumpClause('a', c);
	}

	template<typename VecType>
	void dumpRemoveClause(const VecType & c) {
		dumpClause('d', c);
	}
	template<typename VecType>
	void dumpClause(const char prefix, const VecType & c) {
		fputc_unlocked(prefix, proof);
		for (int i = 0; i < c.size(); ++i)
			dumpLit(toInt(c[i]));
		dumpLit(0);
	}
	void dumpLit(int l) {
		while (l > 127) {
			fputc_unlocked(128 | (l & 127), proof);
			l >>= 7;
		}
		fputc_unlocked(l, proof);
	}

private:
	FILE * proof;
};

#endif /* MTL_DRATPRINT_H_ */
