/*
  ==============================================================================

    WavetableLFO.cpp
    Created: 3 Feb 2023 12:45:49pm
    Author:  honza

  ==============================================================================
*/

#include "WavetableLFO.h"


WavetableLFO::WavetableLFO()
{
    addAndMakeVisible(canvas1);
    addAndMakeVisible(canvas2);
    addAndMakeVisible(canvas3);
    addAndMakeVisible(canvas4);
    addAndMakeVisible(combineButton);
    combineButton.addListener(this);
    addListeners();
    addAndMakeVisible(wavetableSettings);
}

WavetableLFO::~WavetableLFO()
{
    removeListeners();
}

void WavetableLFO::addListeners()
{
    wavetableSettings.rateKnob.slider.addListener(this);
}

void WavetableLFO::removeListeners()
{
    wavetableSettings.rateKnob.slider.removeListener(this);

}

void WavetableLFO::sliderValueChanged(Slider* slider)
{
    if (slider == &wavetableSettings.rateKnob.slider)
    {
        frequency = wavetableSettings.rateKnob.slider.getValue();
        increment = frequency /(float) 440.f;
    }
}

void WavetableLFO::paint(Graphics& g)
{
    g.fillAll(C_DARK);
    paintLogoOnce(g);

}


void WavetableLFO::paintLogoOnce(Graphics& g)
{
    const Image logo = ImageFileFormat::loadFrom(BinaryData::logo250_png, BinaryData::logo250_pngSize);
    g.drawImageAt(logo, (50 - 36) / 2, 7, false);

}

void WavetableLFO::resized()
{
    FlexBox fb{
           FlexBox::Direction::row,
           FlexBox::Wrap::noWrap,
           FlexBox::AlignContent::center,
           FlexBox::AlignItems::center,
           FlexBox::JustifyContent::flexEnd
    };
    Utils::addToFb(&fb, combineButton, 0, 80, 50);
    fb.performLayout(getLocalBounds().withTrimmedLeft(250).withTrimmedBottom(getHeight() - 50));

    int margin = 25;
    canvas1.setBounds(getLocalBounds().withTrimmedLeft(margin).withTrimmedTop(100).withTrimmedBottom(getHeight()/ 2).withTrimmedRight(margin + (W_WIDTH * 3/4)));
    canvas2.setBounds(getLocalBounds().withTrimmedLeft(margin + (W_WIDTH * 1 / 4)).withTrimmedTop(100).withTrimmedBottom(getHeight() / 2).withTrimmedRight(margin + (W_WIDTH * 2 / 4)));
    canvas3.setBounds(getLocalBounds().withTrimmedLeft(margin + (W_WIDTH * 2 / 4)).withTrimmedTop(100).withTrimmedBottom(getHeight() / 2).withTrimmedRight(margin + (W_WIDTH * 1 / 4)));
    canvas4.setBounds(getLocalBounds().withTrimmedLeft(margin + (W_WIDTH * 3 / 4)).withTrimmedTop(100).withTrimmedBottom(getHeight() / 2).withTrimmedRight(margin));

    wavetableSettings.setBounds(getLocalBounds()
        .withTrimmedTop((getHeight()* 2/3) * 1.01)
        .withTrimmedLeft(getWidth() * 0.01)
        .withTrimmedRight(getWidth() * 0.01)
        .withTrimmedBottom(getWidth() * 0.01)
    );
}

void WavetableLFO::buttonClicked(Button* button)
{
    if (button == & combineButton)
    {
        sampleY.clear();

        if (canvas1.waveTableSamples.size() > 0 &&
            canvas2.waveTableSamples.size() > 0 &&
            canvas3.waveTableSamples.size() > 0)
        {
            initSamples();
            canvas4.setWaveForm(sampleY);
        }
    }
}

void WavetableLFO::initSamples()
{
    // samples from canvas1 to canvas2
    // canvas 1 samples
    for (int i = 0; i < canvas1.waveTableSamples.size(); i++)
    {
        sampleY.add(canvas1.waveTableSamples[i]);
    }   

    // split waves between 1-2 && 2-3
    int semiWaves = wavetableSettings.getWaveCount() / 2;

    Array<Array<float>> samplesForEachWave;
    for (int sampleIndex = 0; sampleIndex < canvas1.waveTableSamples.size(); sampleIndex++)
    {
        Array<float> onePointEachWave;
        onePointEachWave.add(canvas1.waveTableSamples[sampleIndex]);
        for (int waveindex = 0; waveindex < semiWaves; waveindex++)
        {
            float y2 = canvas2.waveTableSamples[sampleIndex];
            float y1 = onePointEachWave.getLast();
            int x1 = waveindex;
            int x2 = semiWaves+1;
            //float y = (y1 + (x - x1) * (y2 - y1) / (x2 - x1));
            float y = (y1 + (x1+1 - x1) * (y2 - y1) / (x2 - x1));

            onePointEachWave.add(y);
        }
        samplesForEachWave.add(onePointEachWave);
    }

    for (int waveIndex = 0; waveIndex < semiWaves; waveIndex++)
    {
        for (int sampleIndex = 0; sampleIndex < samplesForEachWave.size(); sampleIndex++)
        {
            sampleY.add(samplesForEachWave[sampleIndex][waveIndex]);
        }
    }

    // add second wave
    for (int i = 0; i < canvas2.waveTableSamples.size(); i++)
    {
        sampleY.add(canvas2.waveTableSamples[i]);
    }

    samplesForEachWave.clear();
    for (int sampleIndex = 0; sampleIndex < canvas2.waveTableSamples.size(); sampleIndex++)
    {
        Array<float> onePointEachWave;
        onePointEachWave.add(canvas2.waveTableSamples[sampleIndex]);
        for (int waveindex = 0; waveindex < semiWaves; waveindex++)
        {
            float y2 = canvas3.waveTableSamples[sampleIndex];
            float y1 = onePointEachWave.getLast();
            int x1 = waveindex;
            int x2 = semiWaves + 1;
            //float y = (y1 + (x - x1) * (y2 - y1) / (x2 - x1));
            float y = (y1 + (x1 + 1 - x1) * (y2 - y1) / (x2 - x1));

            onePointEachWave.add(y);
        }
        samplesForEachWave.add(onePointEachWave);
    }

    for (int waveIndex = 0; waveIndex < semiWaves; waveIndex++)
    {
        for (int sampleIndex = 0; sampleIndex < samplesForEachWave.size(); sampleIndex++)
        {
            sampleY.add(samplesForEachWave[sampleIndex][waveIndex]);
        }
    }


    // add last wave
    for (int i = 0; i < canvas3.waveTableSamples.size(); i++)
    {
        sampleY.add(canvas3.waveTableSamples[i]);
    }
}

float WavetableLFO::getNext()
{

    if (sampleY.size() != (wavetableSettings.getWaveCount() + 3) * 100)
    {
        return 0;
    }

    float totalPosition = fmod((currentPosition * increment), sampleY.size());

    if (totalPosition < 0)
    {
        totalPosition = sampleY.size() - fmod(abs(totalPosition), sampleY.size());
    }

    if (totalPosition > sampleY.size() || totalPosition + 2 > sampleY.size())
    {
        totalPosition = fmod(totalPosition, sampleY.size());
    }

    float finalSample = interpolate(totalPosition, (int)std::floor(totalPosition) % sampleY.size(), (int)std::ceil(totalPosition + 1) % sampleY.size(), sampleY[(int)std::floor(totalPosition) % sampleY.size()], sampleY[(int)std::ceil(totalPosition + 1) % sampleY.size()]);

    currentPosition++;

    return finalSample * wavetableSettings.getDepth();
}

float WavetableLFO::interpolate(float x, float x1, float x2, float y1, float y2)
{
    return y1 + ((x - x1) * ((y2 - y1) / (x2 - x1)));
}

