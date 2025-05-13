#ifndef WORDGRAPH_H
#define WORDGRAPH_H

#include <QMap>
#include <QGraphicsScene>

class WordGraph {
public:
    WordGraph();
    void drawLineGraph(const QMap<QString, int>& wordFrequencies, QGraphicsScene* scene);
};

#endif // WORDGRAPH_H
