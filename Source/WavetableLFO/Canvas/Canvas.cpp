/*
  ==============================================================================

    Canvas.cpp
    Created: 3 Feb 2023 1:46:11pm
    Author:  honza

  ==============================================================================
*/

#include "Canvas.h"

Canvas::Canvas()
{
}

Canvas::~Canvas()
{
}

void Canvas::paintPath(Graphics& g)
{

    Path path;
    path.startNewSubPath(xPos.getFirst(), yPos.getFirst());
    for (int i = 1; i < xPos.size(); i++)
    {
        path.lineTo(xPos[i], yPos[i]);
    }
    g.setColour(Colours::white);
    g.strokePath(path, PathStrokeType(2.0f, PathStrokeType::JointStyle::curved, PathStrokeType::rounded));
}

void Canvas::paint(Graphics& g)
{
    g.fillAll(L_GRAY);
    paintPath(g);
}

void Canvas::mouseDrag(const MouseEvent& e)
{
    addPoint(e.x, e.y);
}

float Canvas::snapToClosestXPoint(float xValue)
{

    float absMin = fabs(xValue - (sampleDistance * 0));
    int closestPointIndex = 0;
    //DBG("sampleDistance" << sampleDistance);
    //DBG("Hledame min k " << xValue);

    for (int i = 1; i < waveTableSampleCount; i++)
    {
        float tmpAbs = fabs(xValue - (sampleDistance * i));
        //DBG(tmpAbs << " < " << absMin);

        if (tmpAbs < absMin) {
            absMin = fabs(xValue - (sampleDistance * i));
            closestPointIndex = i;
        }
    }

    //DBG("Snap nalezena" << sampleDistance * closestPointIndex);
    return sampleDistance * closestPointIndex;
}

void Canvas::addPoint(float newX, float newY)
{

    //DBG("AddPoint newX: " << newX << " , newY:" << newY);
    // Filter out
    if (newX > getWidth() ||
        newX < 0 ||
        newY > getHeight() ||
        newY < 0 ||
        xPos.size() == waveTableSampleCount) 
    {
        return;
    }

    // First value only
    if (xPos.size() == 0)
    {
        //DBG("First value");
        xPos.add(0);
        yPos.add(newY);
        return;
    }

    newX = snapToClosestXPoint(newX);
    //newY = snapToClosestYPoint(newX);

    // Check for X duplicate
    // Check mouse is moving forward only
    if (xPos.indexOf(newX) != -1) {
        //DBG("Existing");
        //DBG("newX: " << newX << " xPos.getLast(): " << xPos.getLast());

        return;
    }
    if (xPos.getLast() >= newX)
    {
        //DBG("old one is bigger than new one");
        return;
    }

    // Check that every new element to be added did not skip previous X point
    // This prevents mouse skipping pixels 
    if (xPos.size() * sampleDistance != newX)
    {
        //DBG("SKIPPED X: " << (xPos.size() * sampleDistance) << " we want to add: " << newX);
        // create skipped value average from last one and current one => their position is counted from left top corner


        int lastIndex = xPos.indexOf(xPos.getLast());

        for (int i = lastIndex + 1; i < (newX / sampleDistance); i++)
        {
            //DBG("want to add x: " << i * sampleDistance << " y: " << newY);
            addPoint(i * sampleDistance, newY);
        }
        return;
    }

    // Finally add values after filtering
    //DBG("ADDED x: " << newX << " y: " << newY);
    xPos.add(newX);
    yPos.add(newY);   

    // Skip repainting if there are less than 2 points.
    if (xPos.size() >= 2) {
        repaint();
    }
}

void Canvas::mouseDown(const MouseEvent& e)
{
    // Clear X and Y points
    xPos.clear();
    yPos.clear();

    // Clear audio samples
    waveTableSamples.clear();

    addPoint(e.x, e.y);
}

float Canvas::interpolateY(float x, float x1, float y1, float x2, float y2)
{
    return(y1 + (x - x1) * (y2 - y1) / (x2 - x1));
}

void Canvas::mouseUp(const MouseEvent& e)
{
    
    // Interpolate wavetable
    if (xPos.size() != waveTableSampleCount)
    {
        //Has to be defined, because each loop xPos size is larger thus infinite loop
        int size = xPos.size();

        for (int i = 1; i <= (waveTableSampleCount - size); i++)
        {
            // Linear interpolation
            // y = y1 + (x - x1) * ( y2 - y1) / ( x2 - x1 )
            //DBG(" Interpolating x:" << xPos.getLast() + sampleDistance);
            float x = xPos.getLast() + sampleDistance;
            float y = interpolateY(x, xPos.getLast(), yPos.getLast(), getWidth(), yPos.getLast());
            addPoint(x, y);
        }
    }
    convertPointsToAmplitude();
}

void Canvas::convertPointsToAmplitude()
{
    // Somehow array set is reverted, but now its not ???
    for (int i = 0; i < yPos.size(); i++)
    {
        waveTableSamples.add(yValueToAmplitude(yPos[i]));
    }
}

float Canvas::yValueToAmplitude(float yVal)
{

    return jlimit(-1.f, 1.f, 1.f - ((2 * yVal) / getHeight()));
}
