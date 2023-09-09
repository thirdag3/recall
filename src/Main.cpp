#include <iostream>
#include <assimp/DefaultLogger.hpp>

int main(int argc, const char** argv)
{
    Assimp::Logger* l = Assimp::DefaultLogger::create("log.txt");
    l->info("This is clearly a very functional and performant application. Nothing to see here.");
    delete l;
}
