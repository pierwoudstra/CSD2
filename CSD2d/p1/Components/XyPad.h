#pragma once

#include <JuceHeader.h>

namespace Gui {
class XYPad : public Component, juce::Slider::Listener {
public:
  /*
   * define axis
   */
  enum class Axis { X1, X2, X3, Y1, Y2, Y3 };

  /*
   * thumb
   */

  class Thumb : public Component {
  public:
    Thumb(Colour colour) {
      this->colour = colour;
      constrainer.setMinimumOnscreenAmounts(thumbSize, thumbSize, thumbSize,
                                            thumbSize);
    }

    void paint(Graphics &g) override {
      g.setColour(colour);
      g.fillEllipse(getLocalBounds().toFloat());
    }

    void mouseDown(const MouseEvent &event) override {
      dragger.startDraggingComponent(this, event);
    }

    void mouseDrag(const MouseEvent &event) override {
      dragger.dragComponent(this, event, &constrainer);
      if (moveCallback)
        moveCallback(getPosition().toDouble());
    }

    // function returns void but accepts position parameter
    std::function<void(Point<double>)> moveCallback;

  private:
    Colour colour;
    ComponentDragger dragger;
    // make sure thumb stays between bounds
    ComponentBoundsConstrainer constrainer;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Thumb)
  };

  /*
   * xy-pad
   */

  XYPad() {
    addAndMakeVisible(thumb);
    addAndMakeVisible(thumb2);
    addAndMakeVisible(thumb3);

    // lambda function
    thumb.moveCallback = [&](Point<double> position) {
      const std::lock_guard<std::mutex> lock(vectorMutex);
      const auto bounds = getLocalBounds().toDouble();
      const auto w = double(thumbSize);

      // x-axis sliders

      for (auto *slider : x1Slider) {
        slider->setValue(jmap(position.getX(), 0.0, bounds.getWidth() - w,
                              slider->getMinimum(), slider->getMaximum()));
      }

      // y-axis sliders

      for (auto *slider : y1Slider) {
        slider->setValue(jmap(position.getY(), bounds.getHeight() - w, 0.0,
                              slider->getMinimum(), slider->getMaximum()));
      }
    };

    thumb2.moveCallback = [&](Point<double> position) {
      const std::lock_guard<std::mutex> lock(vectorMutex);
      const auto bounds = getLocalBounds().toDouble();
      const auto w = double(thumbSize);

      // x-axis sliders

      for (auto *slider : x2Slider) {
        slider->setValue(jmap(position.getX(), 0.0, bounds.getWidth() - w,
                              slider->getMinimum(), slider->getMaximum()));
      }

      // y-axis sliders

      for (auto *slider : y2Slider) {
        slider->setValue(jmap(position.getY(), bounds.getHeight() - w, 0.0,
                              slider->getMinimum(), slider->getMaximum()));
      }
    };

    thumb3.moveCallback = [&](Point<double> position) {
      const std::lock_guard<std::mutex> lock(vectorMutex);
      const auto bounds = getLocalBounds().toDouble();
      const auto w = double(thumbSize);

      // x-axis sliders

      for (auto *slider : x3Slider) {
        slider->setValue(jmap(position.getX(), 0.0, bounds.getWidth() - w,
                              slider->getMinimum(), slider->getMaximum()));
      }

      // y-axis sliders

      for (auto *slider : y3Slider) {
        slider->setValue(jmap(position.getY(), bounds.getHeight() - w, 0.0,
                              slider->getMinimum(), slider->getMaximum()));
      }
    };
  }

  void resized() override {
    thumb.setBounds(
        getLocalBounds().withSizeKeepingCentre(thumbSize, thumbSize));
    if (!x1Slider.empty())
      sliderValueChanged(x1Slider[0]);
    if (!y1Slider.empty())
      sliderValueChanged(y1Slider[0]);

    thumb2.setBounds(
        getLocalBounds().withSizeKeepingCentre(thumbSize, thumbSize));
    if (!x2Slider.empty())
    sliderValueChanged(x2Slider[0]);
    if (!y2Slider.empty())
      sliderValueChanged(y2Slider[0]);

    thumb3.setBounds(
            getLocalBounds().withSizeKeepingCentre(thumbSize, thumbSize));
    if (!x3Slider.empty())
        sliderValueChanged(x3Slider[0]);
    if (!y3Slider.empty())
      sliderValueChanged(y3Slider[0]);
  }

  void paint(Graphics &g) override {
    //    g.setColour(Colours::aliceblue);
    //    g.fillRoundedRectangle(getLocalBounds().toFloat(), 20.f);
  }

  void registerSlider(Slider *slider, Axis axis) {
     slider->addListener(this);
    // lock
    const std::lock_guard<std::mutex> lock(vectorMutex);

    // add elements to the end
    if (axis == Axis::X1)
      x1Slider.push_back(slider);
    if (axis == Axis::X2)
      x2Slider.push_back(slider);
    if (axis == Axis::X3)
      x3Slider.push_back(slider);
    if (axis == Axis::Y1)
      y1Slider.push_back(slider);
    if (axis == Axis::Y2)
      y2Slider.push_back(slider);
    if (axis == Axis::Y3)
      y3Slider.push_back(slider);
  }

  void deregisterSlider(Slider *slider) {
     slider->removeListener(this);
    // lock
    const std::lock_guard<std::mutex> lock(vectorMutex);

    // remove/ erase idiom
    x1Slider.erase(std::remove(x1Slider.begin(), x1Slider.end(), slider),
                   x1Slider.end());
    x2Slider.erase(std::remove(x2Slider.begin(), x2Slider.end(), slider),
                   x2Slider.end());
    x3Slider.erase(std::remove(x3Slider.begin(), x3Slider.end(), slider),
                   x3Slider.end());
    y1Slider.erase(std::remove(y1Slider.begin(), y1Slider.end(), slider),
                   y1Slider.end());
    y2Slider.erase(std::remove(y2Slider.begin(), y2Slider.end(), slider),
                   y2Slider.end());
    y3Slider.erase(std::remove(y3Slider.begin(), y3Slider.end(), slider),
                   y3Slider.end());
  }

  void sliderValueChanged(juce::Slider *slider /* std::string ID , double value */) {
    // add listener of some sort
    if (thumb.isMouseOverOrDragging(false) ||
        thumb2.isMouseOverOrDragging(false) ||
        thumb3.isMouseOverOrDragging(false))
      return;

    const auto isX1Slider =
        std::find(x1Slider.begin(), x1Slider.end(), slider) != x1Slider.end();

    const auto isX2Slider =
        std::find(x2Slider.begin(), x2Slider.end(), slider) != x2Slider.end();

    const auto isX3Slider =
        std::find(x3Slider.begin(), x3Slider.end(), slider) != x3Slider.end();

    const auto isY1Slider =
        std::find(y1Slider.begin(), y1Slider.end(), slider) != y1Slider.end();

    const auto isY2Slider =
        std::find(y2Slider.begin(), y2Slider.end(), slider) != y2Slider.end();

    const auto isY3Slider =
        std::find(y3Slider.begin(), y3Slider.end(), slider) != y3Slider.end();

    const auto bounds = getLocalBounds().toDouble();
    const auto w = static_cast<double>(thumbSize);

    // x1 & y1
    if (isX1Slider) {
      thumb.setTopLeftPosition(jmap(slider->getValue(), slider->getMinimum(),
                                    slider->getMaximum(), 0.0,
                                    bounds.getWidth() - w),
                               thumb.getY());
    } else if (isY1Slider) {
      thumb.setTopLeftPosition(thumb.getX(),
                               jmap(slider->getValue(), slider->getMinimum(),
                                    slider->getMaximum(),
                                    bounds.getHeight() - w, 0.0));
    }

    // x2 & y2
    if (isX2Slider) {
      thumb2.setTopLeftPosition(jmap(slider->getValue(), slider->getMinimum(),
                                     slider->getMaximum(), 0.0,
                                     bounds.getWidth() - w),
                                thumb2.getY());
    } else if (isY2Slider) {
      thumb2.setTopLeftPosition(thumb2.getX(),
                                jmap(slider->getValue(), slider->getMinimum(),
                                     slider->getMaximum(),
                                     bounds.getHeight() - w, 0.0));
    }

    // x3 & y3
    if (isX3Slider) {
      thumb3.setTopLeftPosition(jmap(slider->getValue(), slider->getMinimum(),
                                     slider->getMaximum(), 0.0,
                                     bounds.getWidth() - w),
                                thumb3.getY());
    } else if (isY3Slider) {
      thumb3.setTopLeftPosition(thumb3.getX(),
                                jmap(slider->getValue(), slider->getMinimum(),
                                     slider->getMaximum(),
                                     bounds.getHeight() - w, 0.0));
    }

    repaint();
  }

private:
  std::vector<Slider *> x1Slider, x2Slider, x3Slider, y1Slider, y2Slider,
      y3Slider;
  Thumb thumb = Thumb(juce::Colour(255, 150, 150));
  Thumb thumb2 = Thumb(juce::Colour(150, 255, 150));
  Thumb thumb3 = Thumb(juce::Colour(150, 150, 255));

  std::mutex vectorMutex;

  static constexpr int thumbSize = 40;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(XYPad)
};

} // namespace Gui
