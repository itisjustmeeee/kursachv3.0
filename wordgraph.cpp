#include "wordgraph.h"
#include <QGraphicsPathItem>
#include <QGraphicsLineItem>
#include <QGraphicsTextItem>
#include <QPainterPath>
#include <QList>
#include <QPair>
#include <algorithm>
#include <QtMath>

WordGraph::WordGraph() {}

void WordGraph::drawLineGraph(const QMap<QString, int>& wordFrequencies, QGraphicsScene* scene) {
    if (wordFrequencies.isEmpty()) return;

    const int graphWidth = 1000;
    const int graphHeight = 180;
    const int marginX = 50;
    const int marginY = 30;
    const int axisLabelOffset = 3;
    const int maxWords = 10;

    int maxCount = 0;
    for (int count : wordFrequencies) {
        if (count > maxCount) maxCount = count;
    }
    if (maxCount == 0) return;

    QList<QPair<QString, int>> sortedWords;
    for (auto it = wordFrequencies.constBegin(); it != wordFrequencies.constEnd(); ++it) {
        sortedWords.append(qMakePair(it.key(), it.value()));
    }

    std::sort(sortedWords.begin(), sortedWords.end(),
              [](const QPair<QString, int>& a, const QPair<QString, int>& b) {
                  if (a.second != b.second) {
                      return a.second > b.second;
                  }
                  return a.first < b.first;
              });

    if (sortedWords.size() > maxWords) {
        sortedWords = sortedWords.mid(0, maxWords);
    }

    std::sort(sortedWords.begin(), sortedWords.end(),
              [](const QPair<QString, int>& a, const QPair<QString, int>& b) {
                  if (a.second != b.second) {
                      return a.second < b.second;
                  }
                  return a.first < b.first;
              });

    QStringList words;
    QList<int> frequencies;
    for (const auto& pair : sortedWords) {
        words.append(pair.first);
        frequencies.append(pair.second);
    }

    int pointCount = words.size();
    qreal xStep = pointCount > 1 ? (qreal)(graphWidth - marginX) / (pointCount - 1) : graphWidth - marginX;

    qreal yScale = maxCount > 0 ? (qreal)(graphHeight - marginY) / maxCount : 1.0;

    QGraphicsLineItem* xAxis = new QGraphicsLineItem(marginX, graphHeight, graphWidth, graphHeight);
    xAxis->setPen(QPen(Qt::black, 1));
    scene->addItem(xAxis);

    QGraphicsLineItem* yAxis = new QGraphicsLineItem(marginX, marginY, marginX, graphHeight);
    yAxis->setPen(QPen(Qt::black, 1));
    scene->addItem(yAxis);

    for (int i = 0; i <= maxCount; ++i) {
        if (maxCount <= 5 || i % (maxCount / 5 + 1) == 0) {
            qreal y = graphHeight - i * yScale;
            QGraphicsTextItem* label = new QGraphicsTextItem(QString::number(i));
            label->setDefaultTextColor(Qt::black);
            label->setPos(marginX - axisLabelOffset - label->boundingRect().width(), y - label->boundingRect().height() / 2);
            scene->addItem(label);

            QGraphicsLineItem *gridLine = new QGraphicsLineItem(marginX, y, graphWidth, y);
            gridLine->setPen(QPen(Qt::gray, 0.5, Qt::DashLine));
            scene->addItem(gridLine);

            QGraphicsLineItem* tick = new QGraphicsLineItem(marginX - 5, y, marginX, y);
            tick->setPen(QPen(Qt::black, 1));
            scene->addItem(tick);
        }
    }

    for (int i = 0; i < pointCount; ++i) {
        qreal x = marginX + i * xStep;
        QGraphicsTextItem* label = new QGraphicsTextItem(words[i]);
        label->setDefaultTextColor(Qt::black);
        qreal labelWidth = label->boundingRect().width() * qCos(qDegreesToRadians(30));
        qreal labelHeight = label->boundingRect().height() * qSin(qDegreesToRadians(30));
        label->setPos(x - labelWidth / 2, graphHeight + axisLabelOffset + labelHeight);
        scene->addItem(label);

        QGraphicsLineItem* tick = new QGraphicsLineItem(x, graphHeight, x, graphHeight + 5);
        tick->setPen(QPen(Qt::black, 1));
        scene->addItem(tick);
    }

    QPainterPath path;
    for (int i = 0; i < pointCount; ++i) {
        qreal x = marginX + i * xStep;
        qreal y = graphHeight - frequencies[i] * yScale;

        if (i == 0) {
            path.moveTo(x, y);
        } else {
            path.lineTo(x, y);
        }

        QGraphicsEllipseItem* point = new QGraphicsEllipseItem(x - 2.5, y - 2.5, 5, 5);
        point->setBrush(Qt::red);
        point->setPen(Qt::NoPen);
        scene->addItem(point);
    }

    QGraphicsPathItem* line = new QGraphicsPathItem(path);
    line->setPen(QPen(Qt::blue, 1));
    scene->addItem(line);

    QGraphicsTextItem* xLabel = new QGraphicsTextItem("Words");
    xLabel->setDefaultTextColor(Qt::black);
    xLabel->setPos(graphWidth - xLabel->boundingRect().width() + 55, graphHeight + axisLabelOffset + 25);
    scene->addItem(xLabel);

    QGraphicsTextItem* yLabel = new QGraphicsTextItem("Frequency");
    yLabel->setDefaultTextColor(Qt::black);
    yLabel->setRotation(-90);
    yLabel->setPos(marginX - axisLabelOffset - 30, marginY);
    scene->addItem(yLabel);
}
