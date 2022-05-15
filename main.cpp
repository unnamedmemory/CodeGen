#include <iostream>

#include <clang/ASTMatchers/ASTMatchFinder.h>
#include <clang/ASTMatchers/ASTMatchers.h>
#include <clang/Frontend/FrontendActions.h>
#include <clang/Tooling/CommonOptionsParser.h>
#include <clang/Tooling/Tooling.h>
#include <llvm/Support/Error.h>

using namespace llvm;
using namespace clang;
using namespace clang::tooling;
using namespace clang::ast_matchers;

cl::OptionCategory category("MyOptionCategory");

DeclarationMatcher matcher = cxxRecordDecl(hasName("IDirect3D9"), isDerivedFrom("IUnknown")).bind("D3D9");

class Printer : public MatchFinder::MatchCallback
{
public:
	virtual void run(const MatchFinder::MatchResult& result)
	{
		const CXXRecordDecl* decl = result.Nodes.getNodeAs<CXXRecordDecl>("D3D9");
		if (decl)
		{
			decl->dump();
		}
	}
};

// .\helloworld.exe ..\test.cpp -p="compile_commands.json"
// --extra-arg="-IC:\\msys64\\clang64\\lib\\clang\\14.0.3\\include"

int main(int argc, const char** argv)
{
	Expected<CommonOptionsParser> expected = CommonOptionsParser::create(argc, argv, category);
	if (!expected)
	{
		llvm::errs() << expected.takeError();
		return 1;
	}
	CommonOptionsParser& parser = expected.get();
	ClangTool tool(parser.getCompilations(), parser.getSourcePathList());

	Printer printer;
	MatchFinder finder;
	finder.addMatcher(matcher, &printer);

	return tool.run(newFrontendActionFactory(&finder).get());
}
