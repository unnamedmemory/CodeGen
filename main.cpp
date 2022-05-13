#include <iostream>

#include <clang/Frontend/FrontendActions.h>
#include <clang/Tooling/CommonOptionsParser.h>
#include <clang/Tooling/Tooling.h>
#include <llvm/Support/Error.h>

using namespace llvm;
using namespace clang;
using namespace clang::tooling;

cl::OptionCategory category("MyOptionCategory");

int main(int argc, const char** argv)
{
	Expected<CommonOptionsParser> expected = CommonOptionsParser::create(argc, argv, category);
	if (!expected)
	{
		// Fail gracefully for unsupported options.
		llvm::errs() << expected.takeError();
		return 1;
	}
	CommonOptionsParser& parser = expected.get();
	ClangTool tool(parser.getCompilations(), parser.getSourcePathList());

	return tool.run(newFrontendActionFactory<SyntaxOnlyAction>().get());
}
