# 🎮 TouchInputSystem

[![UE5 Ready](https://img.shields.io/badge/Unreal-5.x-blue)](#)
[![Enhanced Input](https://img.shields.io/badge/Enhanced%20Input-Supported-success)](#)
[![Mobile AAA](https://img.shields.io/badge/Quality-AAA%20(Mobile)-brightgreen)](#)
[![License: MIT](https://img.shields.io/badge/License-MIT-lightgrey.svg)](LICENSE)

**TouchInputSystem** is a next‑generation touch input plugin for **Unreal Engine 5** that delivers **AAA-quality controls** on par with **PUBG Mobile** and **Call of Duty: Mobile**.  
It integrates **directly** with Unreal's **Enhanced Input System** (Input Actions + Mapping Contexts), and ships with polished UI widgets like a **virtual joystick** and a **touchpad** out of the box.

> Built for performance, extensibility and creator ergonomics — ideal for shooters, action, racing, RTS, and casual titles targeting iOS/Android or any touchscreen platform.

---

## ✨ Highlights

- 🎯 **AAA Mobile Quality** – latency‑aware design, stable gesture filtering, and responsive feel.
- ⚡ **First‑class Enhanced Input** – no boilerplate. Works with `UInputAction`, `UEnhancedInputComponent`, and `UInputMappingContext`.
- 🧩 **Ready‑made Widgets** – `UTouchJoystick` and `UTouchPad` built on a powerful `UBaseTouchButton` foundation.
- 🧠 **Clean Data Layer** – simple, Blueprint‑exposed data types for all touch states.
- 🛠 **Blueprint & C++ Friendly** – bind in Blueprints *or* use low‑level C++ delegates.
- 🚀 **Optimized** – minimal allocations, pooled state, safe singleton delegates, and editor‑friendly tuning.
- 🧪 **Tested Patterns** – supports toggle buttons, passthrough touches, ticked gestures, and multi‑touch routing.

---

## 📦 Installation

1. Copy the `TouchInputSystem/` plugin folder into your project’s `Plugins/` directory:
   ```bash
   YourGame/Plugins/TouchInputSystem/
   ```
2. Launch your project and enable **TouchInputSystem** under **Edit → Plugins**.
3. Ensure **Enhanced Input** is enabled in your project (UE5 default).

---

## 🧭 Folder Structure

```
TouchInputSystem/
├─ TouchInputSystem.Build.cs
├─ TouchInputSystem.h / .cpp                  # Module setup
├─ Common/
│  ├─ Data/EnumsStruct/
│  │  ├─ ETouchMode.h                         # enum class EEnum_TouchMode
│  │  ├─ FInGameButtonData.h                  # configurable button behavior
│  │  └─ FTouchInputInfo.h                    # per‑touch payload
│  ├─ Delegates/
│  │  ├─ UTouchSystemDelegates.h/.cpp         # global multicast (singleton) delegates
│  └─ Library/
│     ├─ TouchInputFunctions.h/.cpp           # Blueprint function library (broadcast helpers)
└─ Widget/
   ├─ BaseTouchButton.h/.cpp                  # reusable base widget
   ├─ Joystick/TouchJoystick.h/.cpp           # virtual joystick
   └─ TouchPad/TouchPad.h/.cpp                # swipe/look touchpad
```

---

## 🧩 Core Types & API

### `EEnum_TouchMode`
Located in `Common/Data/EnumsStruct/ETouchMode.h`

```cpp
UENUM(BlueprintType)
enum class EEnum_TouchMode : uint8
{
    None,
    Pressed,
    Released,
    Moved,
    Tap,
    Hold,
    HoldReleased
};
```

### `FTouchInputInfo`
Located in `Common/Data/EnumsStruct/FTouchInputInfo.h`

```cpp
USTRUCT(BlueprintType)
struct FTouchInputInfo
{
    GENERATED_BODY();

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="TouchSystem")
    FVector FingerLocation = FVector::ZeroVector;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="TouchSystem")
    EEnum_TouchMode TouchEventType = EEnum_TouchMode::None;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="TouchSystem")
    bool bIsToggle = false;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="TouchSystem")
    TEnumAsByte<ETouchIndex::Type> TouchIndex = ETouchIndex::Type::Touch1;
};
```

### `FInGameButtonData`
Located in `Common/Data/EnumsStruct/FInGameButtonData.h`  
Configures how a touch widget behaves (toggle vs momentary, passthrough, ticking, and optional `UInputAction` to tick with). Key properties include:

- `bIsToggleButton`
- `bTickTouchEvent`
- `TouchModeToTick` (`EEnum_TouchMode`)
- `bSeparateActionToTick`
- `UInputAction* InputActionToTick`
- *(plus additional editor‑exposed flags such as passthrough, gameplay tags, etc.)*

### Global Delegates – `UTouchSystemDelegates`
Located in `Common/Delegates/UTouchSystemDelegates.*`

A GC‑safe **singleton** that exposes both **dynamic** (Blueprint) and native **multicast** delegates:

```cpp
// Dynamic (Blueprint assignable)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTouchInputDynMulti, FTouchInputInfo, TouchInput);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnByteDynMulti, uint8, Value);

// Native C++
DECLARE_MULTICAST_DELEGATE_OneParam(FOnTouchInputMulti, FTouchInputInfo);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnVector2DInputMulti, FVector2D);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnByteAndTouchInputMulti, uint8, FTouchInputInfo);
```

> The singleton is created via `Get()` and is `AddToRoot()` to prevent garbage collection.

### Blueprint Helpers – `UTouchInputFunctions`
Located in `Common/Library/TouchInputFunctions.*`

```cpp
UCLASS()
class TOUCHINPUTSYSTEM_API UTouchInputFunctions : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintCallable, Category="TouchInput")
    static void BroadcastTouchInputs(const FTouchInputInfo& TouchInputs);
};
```

---

## 🧱 Widget Layer

### `UBaseTouchButton`
Reusable `UUserWidget` base that handles touch lifecycle + Enhanced Input plumbing.  
Exposes Blueprint‑native events to override:

```cpp
UFUNCTION(BlueprintNativeEvent, Category="BaseInGameButton")
void EventOnPressed(const FVector& FingerLocation);

UFUNCTION(BlueprintNativeEvent, Category="BaseInGameButton")
void EventOnReleased(const FVector& FingerLocation);

UFUNCTION(BlueprintNativeEvent, Category="BaseInGameButton")
void EventOnMoved(const FVector& FingerLocation);

UFUNCTION(BlueprintNativeEvent, Category="BaseInGameButton")
void EventOnEventReceived(const FVector& FingerLocation, EEnum_TouchMode TouchMode);
```

Also provides multicast delegates you can subscribe to from C++ (e.g. `OnPressed`, `OnReleased`, `OnMoved`, `OnEventReceived`). Internally integrates with **Enhanced Input** (`EnhancedInputSubsystems`, `UEnhancedInputComponent`) and routes screen touches to the active widget, including **passthrough** support when desired.

> The base handles per‑frame ticking for gestures when `FInGameButtonData.bTickTouchEvent` is enabled.

### `UTouchJoystick`
A virtual joystick built on `UBaseTouchButton`. Key behavior:

- Computes normalized **direction** and **scale** from touch displacement.
- Gives option to Use a Dedicated Input Action for Sprint, Also Supports Sprint Locking.
- Drives an optional **thumb** image/pad with easing (**`UpdateThumbPad`**, **`RevertThumbPad`**).
- Blueprint‑native event:
  ```cpp
  UFUNCTION(BlueprintNativeEvent)
  void JoystickOutput(const FVector& Direction, const float Scale);
  ```
- Helper:
  ```cpp
  UFUNCTION(BlueprintCallable, BlueprintPure, Category="Joystick")
  FVector2D GetCenterPosition();
  ```

### `UTouchPad`
A look/swipe pad built on `UBaseTouchButton`:

```cpp
UFUNCTION(BlueprintCallable, Category="TouchPad")
void BroadcastControlRotation(const FVector2D ControlRotation);
```

Use it to emit **camera control** deltas or UI‑routed rotation vectors.


## 🧰 Examples You Can Build

- **Shooter** – Left joystick for movement, right touchpad for camera; tap buttons for fire/ADS; hold for continuous fire (ticked input action).
- **Racing** – Joystick for steering + throttle scale; edge taps for brakes; swipe for nitro.
- **RTS/MOBA** – Touchpad to pan camera; tap/hold to select/place; two‑finger swipe to multi‑select.

---

## 🧪 Performance & Quality Notes

- Uses GC‑safe singleton for global delegates (`AddToRoot`/`RemoveFromRoot`).
- Touch math uses Slate’s local/screen conversions for accuracy.
- Thumb visuals are updated with easing and clamped radii to avoid jitter.
- Designed to remain responsive on low‑end Android devices.

---

## 🗺️ Roadmap

- Gesture recorder/replayer for automated testing
- Built‑in visualizers (debug overlay for touch traces)
- More widgets: dual‑zone pad, radial menu, quick‑slots
- Haptics helpers (mobile vibration patterns)

---

## 🤝 Contributing

Issues and PRs are welcome!  
Please include a clear description, reproduction steps (if applicable), and screenshots/GIFs for UI changes.

If this plugin helps you, please ⭐ **star this repository**.







2. Add Below snippet in Player Character or Player Controller
   
[![Blueprint Screenshot](Resources/TouchManagerSetup.png)](https://blueprintue.com/render/bew7nfhf/)
