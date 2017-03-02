#include <llvm/IR/Module.h>
#include <llvm/IR/Function.h>
#include <llvm/PassManager.h>
#include <llvm/IR/CallingConv.h>
#include <llvm/IR/Verifier.h>

#include <llvm/IR/IRBuilder.h>
#include <llvm/Support/SourceMgr.h>
#include <llvm/IR/IRPrintingPasses.h>
/*#include <llvm/Support/Process.h> */
#include <llvm/Support/raw_ostream.h>

using namespace llvm;

Module* makeLLVMModule();

int main(int argc, char const *argv[])
{
    Module* Mod = makeLLVMModule();
    // To print to stdout
    verifyModule(*Mod);

    PassManager PM;
    PM.add(createPrintModulePass(outs()));
    PM.run(*Mod);
    delete Mod;
    return 0;
}


Module* makeLLVMModule() {
    // Module construction
    Module* mod = new Module("test", getGlobalContext());

    Constant* c = mod->getOrInsertFunction("mul_add",
        /*ret type*/                        IntegerType::get(getGlobalContext(), 32),
        /* args */                          IntegerType::get(getGlobalContext(), 32),
                                            IntegerType::get(getGlobalContext(), 32),
                                            IntegerType::get(getGlobalContext(), 32),
                                            NULL);

    Function* mul_add = cast<Function>(c);
    mul_add->setCallingConv(CallingConv::C);

    Function::arg_iterator args = mul_add->arg_begin();
    Value* x = args++;
    x->setName("x");
    Value* y = args++;
    y->setName("y");
    Value* z = args++;
    z->setName("z");

    BasicBlock* block = BasicBlock::Create(getGlobalContext(), "entry", mul_add);
    IRBuilder<> builder(block);

    Value* tmp = builder.CreateBinOp(Instruction::Mul, x, y, "tmp");
    Value* tmp2 = builder.CreateBinOp(Instruction::Add, tmp, z, "tmp2");


    builder.CreateRet(tmp2);

    outs() << "-----";
    outs() << *tmp;
    outs() << "------\n";
    return mod;
}