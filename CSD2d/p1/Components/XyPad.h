#pragma once

#include <JuceHeader.h>

namespace Gui {
  class XYPad : public Component {
  public:
    /*
     * define axis
     */
    enum class Axis {X1, X2, X3, Y1, Y2, Y3};

    /*
     * thumb
     */

    class Thumb : public Component {
    public:
      Thumb() {}
      void paint(Graphics& g) override {
        g.setColour(Colours::white);
        g.fillEllipse(getLocalBounds().toFloat());
      }
    private:
      JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Thumb)
    };

    /*
     * xy-pad
     */

    XYPad() {
      addAndMakeVisible(thumb);

    }
    void resized() override {
      thumb.setBounds(getLocalBounds().withSizeKeepingCentre(thumbSize, thumbSize));
    }
    void paint(Graphics& g) override {}
    void registerSlider(Slider* slider, Axis axis) {}
    void deregisterSlider(Slider* slider) {}

  private:
    std::vector<Slider*> x1Slider, x2Slider, x3Slider, y1Slider, y2Slider, y3Slider;
    Thumb thumb;

    static constexpr int thumbSize = 40;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(XYPad)
  };

}
