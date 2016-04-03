#include "editor_model.h"

editor_model::editor_model(QObject *parent) :
    QObject(parent),
    current_state(PAUSED),
    file_path(""),
    brush_color(QColor::fromRgb(0, 0, 0)),
    current_tool(BRUSH),
    playback_speed(1) { }


//// Animator State ////

void editor_model::setAnimatorState(AnimatorState state)
{
    current_state = state;
}

editor_model::AnimatorState editor_model::getAnimatorState()
{
    return current_state;
}


//// Current Tool ////

void editor_model::setCurrentTool(Tool tool)
{
    current_tool = tool;
}

editor_model::Tool editor_model::getCurrentTool()
{
    return current_tool;
}

//// Should not be necessary ////
//// Sprite Methods ////

void editor_model::setSprite(Sprite *sprite)
{
    this->sprite_main = sprite;
}

Sprite* editor_model::getSprite()
{
    return sprite_main;
}

//// Drawing Methods ////

void editor_model::paintCommand(int x, int y)
{
    if(current_tool == editor_model::BRUSH) {
        drawSquare(x, y);
    } else if (current_tool == editor_model::FILL_BUCKET) {
        fillBucket(x, y);
    } else if (current_tool == editor_model::MIRROR) {
        drawMirror(x, y);
    } else if (current_tool == editor_model::ERASER) {
        eraseSquare(x, y);
    }
}

/**
 * @brief GraphicsScene::drawSquare
 * Draws a square onto the canvas at the x and y pixel positions.
 * Aka. for the paint brush tool.
 * @param x
 * @param y
 * @param color
 */
void editor_model::drawSquare(int x, int y)
{
    if((x < 0) | (y < 0) | (x >= sprite_main->getWidth()) | (y >= sprite_main->getHeight()))
        return;

    sprite_main->setPixelColorAtCurrentFrame(x, y, brush_color);

    emit squareUpdated(x, y);
}

void editor_model::eraseSquare(int x, int y)
{
    if((x < 0) | (y < 0) | (x >= sprite_main->getWidth()) | (y >= sprite_main->getHeight()))
        return;

    sprite_main->setPixelColorAtCurrentFrame(x, y, QColor(0, 0, 0, 0));

    emit squareUpdated(x, y);
}

void editor_model::fillBucket(int x, int y)
{
    QColor prev = sprite_main->getPixelColorAtCurrentFrame(x, y);

    if(prev == brush_color)
        return;

    drawSquare(x, y);


    int width = sprite_main->getWidth();
    int height = sprite_main->getHeight();

    int x1 = x - 1;
    int x2 = x + 1;
    int y1 = y - 1;
    int y2 = y + 1;
    if(x1 >= 0 && sprite_main->getPixelColorAtCurrentFrame(x1, y) == prev)
            fillBucket(x1, y);

    if(x2 < width && sprite_main->getPixelColorAtCurrentFrame(x2, y) == prev)
            fillBucket(x2, y);

    if(y1 >= 0 && sprite_main->getPixelColorAtCurrentFrame(x, y1) == prev)
            fillBucket(x, y1);

    if(y2 < height && sprite_main->getPixelColorAtCurrentFrame(x, y2) == prev)
            fillBucket(x, y2);
}

void editor_model::drawMirror(int x, int y)
{
    drawSquare(x, y);
    drawSquare(sprite_main->getWidth() - 1 - x, y);
}

void editor_model::rotateScene(bool direction)
{
    sprite_main->rotateCurrentFrame(direction);
    emit sceneUpdated();
}

void editor_model::flipSceneOrientation(bool orientation)
{
    sprite_main->flipCurrentFrameOrientation(orientation);
    emit sceneUpdated();
}

void editor_model::invertSceneColors()
{
    sprite_main->invertCurrentFrameColor();
    emit sceneUpdated();
}

//// Frame Methods ////

void editor_model::nextFrame()
{
    sprite_main->nextFrame();
    emit sceneUpdated();
    emit frameUpdated(sprite_main->getCurrentFrameIndex(), sprite_main->getAnimationLength());
}

void editor_model::prevFrame()
{
    sprite_main->prevFrame();
    emit sceneUpdated();
    emit frameUpdated(sprite_main->getCurrentFrameIndex(), sprite_main->getAnimationLength());
}

void editor_model::addFrame()
{
    sprite_main->addFrameAfterCurrentIndex();
    emit sceneUpdated();
    emit frameUpdated(sprite_main->getCurrentFrameIndex(), sprite_main->getAnimationLength());
}

void editor_model::removeFrame()
{
    sprite_main->removeCurrentFrame();
    emit sceneUpdated();
    emit frameUpdated(sprite_main->getCurrentFrameIndex(), sprite_main->getAnimationLength());
}

void editor_model::setCurrentFrame(int index)
{
    if (index == sprite_main->getCurrentFrameIndex())
        return;
    sprite_main->setCurrentFrame(index);
    emit sceneUpdated();
    emit frameUpdated(sprite_main->getCurrentFrameIndex(), sprite_main->getAnimationLength());
}

//// Brush Color ////

void editor_model::setBrushColor(QColor color)
{
    brush_color = color;
}

//QColor editor_model::getBrushColor()
//{
//    return brush_color;
//}

//// Playback Speed ////

void editor_model::setPlaybackSpeed(int speed)
{
    playback_speed = speed;
}

int editor_model::getPlaybackSpeed()
{
    return playback_speed;
}


//// Saving/loading ////

bool editor_model::getFileSavedStatus()
{
    return file_saved;
}

void editor_model::setFileSavedStatus(bool status)
{
    file_saved = status;
}

QString editor_model::getFilePath()
{
    return file_path;
}

void editor_model::saveToFile(QString path)
{
    QFile file(path);
    if (file.open(QIODevice::ReadWrite))
    {
        QTextStream stream(&file);
        stream << sprite_main->toString();
    }

    file_path = path;
}

void editor_model::loadSpriteFromFile(QString path)
{
    QFile file(path);
    if(!file.open(QIODevice::ReadOnly)) {
        //error
        return;
    }
    file_path = path;
    QTextStream in(&file);
//    int numberOfFrames;
    int width, height;
    int currentX = 0;
    int currentY = 0;
    QString size = in.readLine();
    QStringList sizes = size.split(" ");
    width = sizes[0].toInt();
    height = sizes[1].toInt();
    sprite_main = new Sprite(width,height);

    QString num_frames = in.readLine();
//    numberOfFrames = num_frames.toInt();

    while(!in.atEnd())
    {
        int lineCount = 0;
        sprite_main->addFrameAfterCurrentIndex();
        while(lineCount < height)
        {
            currentX = 0;
            QString line = in.readLine();
            QStringList numbers = line.split(" ");

            for(int i = 0; i < numbers.size() - 4; i += 4)
            {
                int red   = numbers[i+0].toInt();
                int green = numbers[i+1].toInt();
                int blue  = numbers[i+2].toInt();
                int alpha = numbers[i+3].toInt();
                QColor color(red, green, blue, alpha);
                sprite_main->setPixelColorAtCurrentFrame(currentX, currentY, color);
                ++currentX;
            }
            ++currentY;
            ++lineCount;
        }

    }
    emit sceneUpdated();
}
