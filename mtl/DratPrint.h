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
#include <iostream>

namespace Glucose {

class DratPrint {
public:
	DratPrint(const bool shouldPrint, const std::string & proofFileName) :
			proof(
					(shouldPrint) ?
							fopen(proofFileName.c_str(), "wb") : NULL) {
	}

	~DratPrint() {
		if (proof != NULL) {
			fclose(proof);
			proof = NULL;
		}
	}

	template<typename VecType>
	void dumpAddClause(const VecType & c) {
		dumpClause('a', c);
	}

	template<typename VecType>
	void dumpAddClauseExcludeLit(const VecType & c, const Lit l) {
		assert(proof != NULL);
		write('a');
		for (int i = 0; i < c.size(); ++i)
			if (c[i] != l)
				dumpLit(c[i]);
		write(0);
	}

	void dumpEmptyClause() {
		dumpClause('a', vec<Lit>());
	}

	template<typename VecType>
	void dumpRemoveClause(const VecType & c) {
		dumpClause('d', c);
	}
	template<typename VecType>
	void dumpClause(const int prefix, const VecType & c) {
		assert(proof != NULL);
		write(prefix);
		for (int i = 0; i < c.size(); ++i)
			dumpLit(c[i]);
		write(0);
	}
	void dumpLit(const Lit in) {
		unsigned l = toInt(in) + 2;
		assert(l > 0u && toInt(in) + 2 > 0);
		while (l > 127u) {
			write(128u + (l & 127u));
			l >>= 7u;
		}
		write(l);
	}

private:
	FILE * proof;

	inline void write(const unsigned & c) {
		putc_unlocked((unsigned char)c, proof);
	}
};
}

#endif /* MTL_DRATPRINT_H_ */

