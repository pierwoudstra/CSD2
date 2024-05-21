#pragma once

#include <JuceHeader.h>

namespace juce {

class CustomLNF : public juce::LookAndFeel_V4 {
public:
  void drawRotarySlider(Graphics &g, int x, int y, int width, int height,
                        float sliderPos, const float rotaryStartAngle,
                        const float rotaryEndAngle, Slider &slider) {
    auto outline = slider.findColour(Slider::rotarySliderOutlineColourId);
    auto fill = slider.findColour(Slider::rotarySliderFillColourId);

    auto bounds = Rectangle<int>(x, y, width, height).toFloat().reduced(10);

    auto radius = jmin(bounds.getWidth(), bounds.getHeight()) / 2.0f;
    auto toAngle =
        rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
    auto lineW = jmin(8.0f, radius * 0.5f);
    auto arcRadius = radius - lineW * 0.5f;

    // dial background path
    Path backgroundArc;
    backgroundArc.addCentredArc(bounds.getCentreX(), bounds.getCentreY(),
                                arcRadius, arcRadius, 0.0f, rotaryStartAngle,
                                rotaryEndAngle, true);

    g.setColour(Colours::yellow);
    g.strokePath(backgroundArc, PathStrokeType(lineW, PathStrokeType::curved,
                                               PathStrokeType::rounded));

    if (slider.isEnabled()) {
      // dial fill path
      Path valueArc;
      valueArc.addCentredArc(bounds.getCentreX(), bounds.getCentreY(),
                             arcRadius, arcRadius, 0.0f, rotaryStartAngle,
                             toAngle, true);

      g.setColour(Colours::yellow);
      g.strokePath(valueArc, PathStrokeType(lineW, PathStrokeType::curved,
                                            PathStrokeType::rounded));
    }

    // thumb
    auto thumbWidth = lineW * 2.0f;
    Point<float> thumbPoint(
        bounds.getCentreX() +
            arcRadius * std::cos(toAngle - MathConstants<float>::halfPi),
        bounds.getCentreY() +
            arcRadius * std::sin(toAngle - MathConstants<float>::halfPi));

    g.setColour(Colours::yellow);
    g.drawLine( backgroundArc.getBounds().getCentreX(), backgroundArc.getBounds().getCentreY(), thumbPoint.getX(), thumbPoint.getY(), lineW );
  }
};

} // namespace juce
