#include "Symbolic/Core/Algorithms/ASTDebugInfo.hpp"
#include "ASTDebugInfoImpl.hpp"
#include <iostream>

namespace Symbolic::Core
{

    ASTDebugInfo::ASTDebugInfo(const Node* node, std::ostream& out) : impl_(std::make_unique<ASTDebugInfoImpl>(node, out)) {}

    std::span<const Node* const> ASTDebugInfo::memory() const {
        return impl_->memory();
    }

    ASTDebugInfo::~ASTDebugInfo() = default;

}