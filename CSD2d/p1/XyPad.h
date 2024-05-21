#pragma once

#include <JuceHeader.h>

namespace Gui {
  class XyPad : public Component {
  public:
    enum class Axis {X, Y};

    /*
     * thumb section
     */
    class Thumb : public Component {
    public:
      Thumb() {}
      void paint(Graphics& g) override {
        g.setColour(juce::Colours::white);
        g.fillEllipse(getLocalBounds.toFloat());
      }
    private:
      JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Thumb);
    };

    XyPad() {}
    void resized() override {
      thumb.setBounds( getLocalBounds().withSizeKeepingCentre(thumbSize, thumbSize) );
    }
    void paint(Graphics& g) override {
      g.setColour(juce::Colours::black);
      g.fillRoundedRectangle(getLocalBounds().toFloat(), 10.f);
    }
    void registerSlider(Slider* slider, Axis) {}
    void deregisterSlider(Slider* slider) {}

  private:
    std::vector<Slider*> xSliders, ySliders;
    Thumb thumb;

    static constexpr int thumbSize = 40;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(XyPad);
  };
}
