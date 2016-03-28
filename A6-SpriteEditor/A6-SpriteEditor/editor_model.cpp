#include "editor_model.h"

editor_model::editor_model(QObject *parent) :
    QObject(parent), brush_color(QColor::fromRgb(255, 255, 255)), current_frame_index(0),
    current_state(PAUSED), current_tool(BRUSH), playback_speed(1)
{

}

void editor_model::setBrushColor(QColor color)
{
    brush_color = color;
}

/**
 * Moves the model to the next frame by incrementing the current_frame_index. If
 * the incremented index is greater than or equal to the length of the number of
 * frames in the sprite, then reset the index back to 0.
 *
 * @brief editor_model::nextFrame
 */
void editor_model::nextFrame()
{
    if (++current_frame_index >= sprite_main.getAnimationLength())
        current_frame_index = 0;
}

/**
 * Moves the model to the previous frame by decrementing the index. If the index
 * is decremented to less than 0, reset the index to the end of the list of frames.
 * @brief editor_model::prevFrame
 */
void editor_model::prevFrame()
{
    if (--current_frame_index < 0)
        current_frame_index = sprite_main.getAnimationLength() - 1;
}

void editor_model::setAnimatorState(AnimatorState state)
{
    current_state = state;
}

editor_model::AnimatorState editor_model::getAnimatorState()
{
    return current_state;
}

void editor_model::setTool(Tool tool)
{
    current_tool = tool;
}

editor_model::Tool editor_model::getTool()
{
    return current_tool;
}

void editor_model::setPlaybackSpeed(int speed)
{
    playback_speed = speed;
}
