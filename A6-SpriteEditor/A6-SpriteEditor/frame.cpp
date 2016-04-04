#include "frame.h"

/**
 * Constructor
 *
 * @brief Frame::Frame
 * @param parent
 */
Frame::Frame(QObject *parent) :
    QObject(parent) { }

/**
 * Constructor
 *
 * @brief Frame::Frame
 * @param parent
 * @param width_
 * @param height_
 */
Frame::Frame(int width_, int height_,QObject *parent) :
    QObject(parent), width(width_), height(height_)
{
    for(int i = 0; i < width; ++i)
    {
        frameMatrix.append(QVector<QColor>(height));
        for(int j = 0; j < height; ++j)
        {
            frameMatrix[i][j] = QColor(0, 0, 0, 0);
        }
    }
}

/**
 * @brief Frame::~Frame
 */
Frame::~Frame() { }

Frame* Frame::clone()
{
    Frame* newFrame = new Frame(this->width, this->height);
    for (int i = 0; i < this->width; ++i)
    {
        for (int j = 0; j < this->height; ++j)
        {
            newFrame->setPixelColor(i, j, this->getPixelColor(i, j));
        }
    }
    return newFrame;
}

/**
 * @brief Frame::setPixelColor
 * @param x
 * @param y
 * @param color
 */
void Frame::setPixelColor(int x, int y, QColor color)
{
    frameMatrix[x][y] = color;
}

/**
 * @brief Frame::setWholeFrameColor
 * @param color
 */
void Frame::setWholeFrameColor(QColor color)
{
    for(int i = 0; i < width; ++i)
        for(int j=0; j < height; ++j)
            frameMatrix[i][j] = color;
}

/**
 * @brief Frame::getPixelColor
 * @param x
 * @param y
 * @return
 */
QColor Frame::getPixelColor(int x, int y)
{
    return frameMatrix[x][y];
}

/**
 * @brief Frame::getFrameWidth
 * @return
 */
int Frame::getFrameWidth()
{
    return width;
}

/**
 * @brief Frame::getFrameHeight
 * @return
 */
int Frame::getFrameHeight()
{
    return height;
}

/**
 * @brief Frame::rotate
 * Rotates the vector of colors in the frame
 * @param direction
 * True: rotates counterclockwise
 * False: rotates clockwise
 */
void Frame::rotate(bool clockwise)
{
    QVector<QVector<QColor>> flipped;
    for (int i = 0; i < height; ++i)
    {
        flipped.append(QVector<QColor>(width));
        for (int j = 0; j < width; ++j)
        {
            if (clockwise)
                flipped[i][j] = frameMatrix[width - 1 - j][i];
            else
                flipped[i][j] = frameMatrix[j][height - 1 - i];
        }
    }
    int temp = width;
    width = height;
    height = temp;
    frameMatrix = flipped;
}

void Frame::flip(bool vertical)
{
    QVector<QVector<QColor>> temp(frameMatrix);
    if (vertical)
    {       
        for (int x = 0; x < width; ++x)
            for (int y = 0; y < height; ++y)
                frameMatrix[x][y] = temp[x][height - 1 - y];
    }
    else
    {
        for (int x = 0; x < width; ++x)
            for (int y = 0; y < height; ++y)
                frameMatrix[x][y] = temp[width - x - 1][y];
    }

}

void Frame::invert()
{
    for (int x = 0; x < width; ++x)
        for (int y = 0; y < height; ++y)
        {
            QColor invert = frameMatrix[x][y];
            invert.setBlue (255 - invert.blue());
            invert.setRed  (255 - invert.red());
            invert.setGreen(255 - invert.green());
            frameMatrix[x][y] = invert;
        }
}

QString Frame::toString()
{
    QString result;
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            QColor color = getPixelColor(x,y);
            result += toRgbaString(color);
        }
        result += "\n";
    }
    return result;
}

QString Frame::toRgbaString(QColor color)
{
    return QString::number(color.red())   + " " +
            QString::number(color.green()) + " " +
            QString::number(color.blue())  + " " +
            QString::number(color.alpha()) + " ";
}

QImage *Frame::toQImage()
{
    QImage *newImage = new QImage(width, height, QImage::Format_ARGB32);
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            QColor tempColor = frameMatrix[i][j];
            newImage->setPixel(i,j,tempColor.rgba());
        }
    }

    return newImage;
}
