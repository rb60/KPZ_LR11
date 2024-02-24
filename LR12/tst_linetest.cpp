
#include <gmock/gmock-matchers.h>
#include <gtest/gtest.h>
#include <QImage>
#include "../layerdrawer.h"


using namespace testing;

TEST(LayerTest, LineTest)
{
    LineLayer layer(QPointF(0, 0), QPointF(1, 1), Qt::black);
    QImage image(100, 100, QImage::Format_RGB32);
    layer.draw({QRect(0,0,100,100), &image});
    EXPECT_EQ(image.pixelColor(0,0), QColor(Qt::black));
}

TEST(LayerTest, LineFrameTest)
{
    LineLayer layer(QPointF(0, 0), QPointF(1, 1), Qt::black);
    QImage image(100, 100, QImage::Format_RGB32);
    layer.draw({QRect(50,0,50,100), &image});
    EXPECT_EQ(image.pixelColor(50,0), QColor(Qt::black));
}

TEST(LayerTest, ArcTest)
{
    ArcLayer layer(QRectF(0, 0, 1, 1), 0, 5760, Qt::black);
    QImage image(100, 100, QImage::Format_RGB32);
    layer.draw({QRect(0,0,100,100), &image});
    EXPECT_EQ(image.pixelColor(50,0), QColor(Qt::black));
}

TEST(LayerTest, ArcFrameTest)
{
    ArcLayer layer(QRectF(0, 0, 1, 1), 0, 5760, Qt::black);
    QImage image(100, 100, QImage::Format_RGB32);
    layer.draw({QRect(50,0,50,100), &image});
    EXPECT_EQ(image.pixelColor(75,0), QColor(Qt::black));
}

TEST(LayerTest, LayingOnTest)
{
    LineLayer layer1(QPointF(0, 0), QPointF(1, 1), Qt::red);
    LineLayer layer2(QPointF(1, 0), QPointF(0, 1), Qt::blue);
    QImage image(100, 100, QImage::Format_RGB32);
    layer1.draw({QRect(0,0,100,100), &image});
    layer2.draw({QRect(0,0,100,100), &image});
    EXPECT_EQ(image.pixelColor(50,50), QColor(Qt::blue));
}


