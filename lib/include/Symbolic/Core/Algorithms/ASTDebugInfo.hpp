#pragma once

#include "Symbolic/Core/AST/Nodes/Node.hpp"
#include "Symbolic/Core/AST/Expression.hpp"
#include <iostream>

namespace Symbolic::Core
{
    // void ASTDebugInfo(const Node*, std::ostream& out = std::cerr);

    class ASTDebugInfoImpl;

    class ASTDebugInfo {
    private:
        std::unique_ptr<ASTDebugInfoImpl> impl_;
    public:
        ASTDebugInfo() = delete;
        ~ASTDebugInfo();
        ASTDebugInfo(const Node*, std::ostream& out = std::cerr);
        
        std::span<const Node* const> memory() const;        
    };
}
