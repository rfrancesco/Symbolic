#pragma once

#include "Symbolic/Core/Types.hpp"

#include "Symbolic/Core/AST/Expression.hpp"
#include "Symbolic/Core/AST/Nodes/Node.hpp"
#include "Symbolic/Core/AST/Nodes/UnaryOperatorNode.hpp"
#include "Symbolic/Core/AST/Nodes/BinaryOperatorNode.hpp"
#include "Symbolic/Core/AST/Nodes/NaryOperatorNode.hpp"
#include "Symbolic/Core/AST/Nodes/Value.hpp"
#include "Symbolic/Core/AST/Nodes/Symbol.hpp"
#include "Symbolic/Core/AST/SymbolContext.hpp"
#include "Symbolic/Core/AST/Nodes/Negative.hpp"
#include "Symbolic/Core/AST/Nodes/Sum.hpp"
#include "Symbolic/Core/AST/Nodes/Product.hpp"
#include "Symbolic/Core/AST/Nodes/Division.hpp"
#include "Symbolic/Core/AST/Nodes/Power.hpp"
#include "Symbolic/Core/AST/Nodes/FunctionNode.hpp"

#include "Symbolic/Core/Functions/Function.hpp"
#include "Symbolic/Core/Functions/CommonFunctions.hpp"

#include "Symbolic/Core/Algorithms/Evaluator.hpp"