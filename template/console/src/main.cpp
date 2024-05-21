
#include "mainnode.h"
#include <QCoreApplication>
#include <stdio.h>

int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);

    MainNode main_node;

    return app.exec();
}
