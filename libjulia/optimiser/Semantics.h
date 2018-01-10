/*
	This file is part of solidity.

	solidity is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	solidity is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with solidity.  If not, see <http://www.gnu.org/licenses/>.
*/
/**
 * Specific AST walkers that collect semantical facts.
 */

#pragma once

#include <libjulia/optimiser/ASTWalker.h>

#include <string>
#include <map>
#include <set>

namespace dev
{
namespace julia
{

/**
 * Specific AST walker that determines whether an expression is movable.
 *
 * NOTE: this will not ensure that an actual Expression is passed and therefore
 *       the Semantics.movable() helper should be used instead.
 */
class MovableChecker: public ASTWalker
{
public:
	using ASTWalker::operator ();
	virtual void operator()(Identifier const& _identifier) override;
	virtual void operator()(FunctionalInstruction const& _functionalInstruction) override;
	virtual void operator()(FunctionCall const& _functionCall) override;

	bool movable() const { return m_movable; }
	std::set<std::string> const& referencedExpressions() const { return m_exprReferences; }

private:
	/// Which identifiers the current expression references.
	std::set<std::string> m_exprReferences;
	/// Is the current expression movable or not.
	bool m_movable = true;
};

struct Semantics
{
	/// Returns true in an expression is movable.
	/// NOTE: do not use MovableChecker directly, but rather through this helper.
	static bool movable(Expression const& _expression);
};

}
}
