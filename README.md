# TouchInputSystem

**TouchInputSystem** is a high-quality Unreal Engine plugin that provides advanced and flexible touch input handling for mobile and touch-enabled platforms.  
It is built with **AAA standards**, similar to what you experience in **PUBG Mobile** and **Call of Duty Mobile**, ensuring smooth and responsive controls for fast-paced, competitive games.

## ✨ Features

- 🎮 **AAA Quality** — tuned for responsiveness and performance, tested against top-tier mobile shooters.
- 🖐️ Supports **tap, swipe, pinch, drag, rotate** gestures.
- 📱 **Multi-touch tracking** with conflict resolution.
- ⚡ **Direct integration with Unreal’s Enhanced Input System** — works seamlessly with the new Input Mapping Context setup.
- 🔧 Fully customizable callbacks in **C++** and **Blueprints**.
- 🔄 Scales easily for different genres (FPS, MOBA, RTS, Racing, Casual).
- 🚀 Optimized for **low-latency input** on Android & iOS.

## 📦 Installation

1. Clone the repo:
   ```bash
   git clone https://github.com/ShawAbhi/TouchInputSystem.git

2. Add Below snippet in Player Character or Player Controller
   
<div style="position: relative;">
<pre><code id="code-block">Begin Object Class=/Script/BlueprintGraph.K2Node_InputTouch Name="K2Node_InputTouch_0" ExportPath="/Script/BlueprintGraph.K2Node_InputTouch'/Game/Blueprints/Pawn/BP_BasePawn.BP_BasePawn:EventGraph.K2Node_InputTouch_0'"
   NodePosX=256
   NodePosY=-384
   NodeGuid=E9E762CF4B5A69DFB4E16F8B54C341A8
   CustomProperties Pin (PinId=71747E5C46A5053287FBAB8156E04742,PinName="Pressed",Direction="EGPD_Output",PinType.PinCategory="exec",PinType.PinSubCategory="",PinType.PinSubCategoryObject=None,PinType.PinSubCategoryMemberReference=(),PinType.PinValueType=(),PinType.ContainerType=None,PinType.bIsReference=False,PinType.bIsConst=False,PinType.bIsWeakPointer=False,PinType.bIsUObjectWrapper=False,PinType.bSerializeAsSinglePrecisionFloat=False,LinkedTo=(K2Node_MacroInstance_1 E4FF9FC341533D603645888EF1D60F0E,),PersistentGuid=00000000000000000000000000000000,bHidden=False,bNotConnectable=False,bDefaultValueIsReadOnly=False,bDefaultValueIsIgnored=False,bAdvancedView=False,bOrphanedPin=False,)
   CustomProperties Pin (PinId=D384F7C14BA527354AAE6293A732E556,PinName="Released",Direction="EGPD_Output",PinType.PinCategory="exec",PinType.PinSubCategory="",PinType.PinSubCategoryObject=None,PinType.PinSubCategoryMemberReference=(),PinType.PinValueType=(),PinType.ContainerType=None,PinType.bIsReference=False,PinType.bIsConst=False,PinType.bIsWeakPointer=False,PinType.bIsUObjectWrapper=False,PinType.bSerializeAsSinglePrecisionFloat=False,LinkedTo=(K2Node_MacroInstance_1 1F9BD817439970D5A565E4946D3E6936,),PersistentGuid=00000000000000000000000000000000,bHidden=False,bNotConnectable=False,bDefaultValueIsReadOnly=False,bDefaultValueIsIgnored=False,bAdvancedView=False,bOrphanedPin=False,)
   CustomProperties Pin (PinId=186B088C45F42F513D5DBAAE614A8D08,PinName="Moved",Direction="EGPD_Output",PinType.PinCategory="exec",PinType.PinSubCategory="",PinType.PinSubCategoryObject=None,PinType.PinSubCategoryMemberReference=(),PinType.PinValueType=(),PinType.ContainerType=None,PinType.bIsReference=False,PinType.bIsConst=False,PinType.bIsWeakPointer=False,PinType.bIsUObjectWrapper=False,PinType.bSerializeAsSinglePrecisionFloat=False,LinkedTo=(K2Node_MacroInstance_1 03130AA3464113E63F0AD789E24D9FD4,),PersistentGuid=00000000000000000000000000000000,bHidden=False,bNotConnectable=False,bDefaultValueIsReadOnly=False,bDefaultValueIsIgnored=False,bAdvancedView=False,bOrphanedPin=False,)
   CustomProperties Pin (PinId=B928E6764BB90A27B411A8825EFB863F,PinName="Location",Direction="EGPD_Output",PinType.PinCategory="struct",PinType.PinSubCategory="",PinType.PinSubCategoryObject="/Script/CoreUObject.ScriptStruct'/Script/CoreUObject.Vector'",PinType.PinSubCategoryMemberReference=(),PinType.PinValueType=(),PinType.ContainerType=None,PinType.bIsReference=False,PinType.bIsConst=False,PinType.bIsWeakPointer=False,PinType.bIsUObjectWrapper=False,PinType.bSerializeAsSinglePrecisionFloat=False,LinkedTo=(K2Node_MacroInstance_1 AEACB43B40F0E3FD69CCE391CAB09FA6,),PersistentGuid=00000000000000000000000000000000,bHidden=False,bNotConnectable=False,bDefaultValueIsReadOnly=False,bDefaultValueIsIgnored=False,bAdvancedView=False,bOrphanedPin=False,)
   CustomProperties Pin (PinId=6C193C104799BCCD7B82B6BCEAAA0D95,PinName="FingerIndex",Direction="EGPD_Output",PinType.PinCategory="byte",PinType.PinSubCategory="",PinType.PinSubCategoryObject="/Script/CoreUObject.Enum'/Script/InputCore.ETouchIndex'",PinType.PinSubCategoryMemberReference=(),PinType.PinValueType=(),PinType.ContainerType=None,PinType.bIsReference=False,PinType.bIsConst=False,PinType.bIsWeakPointer=False,PinType.bIsUObjectWrapper=False,PinType.bSerializeAsSinglePrecisionFloat=False,LinkedTo=(K2Node_MacroInstance_1 0DB0546945E2A07E0453A7870CCB4BFE,),PersistentGuid=00000000000000000000000000000000,bHidden=False,bNotConnectable=False,bDefaultValueIsReadOnly=False,bDefaultValueIsIgnored=False,bAdvancedView=False,bOrphanedPin=False,)
End Object
Begin Object Class=/Script/BlueprintGraph.K2Node_MacroInstance Name="K2Node_MacroInstance_1" ExportPath="/Script/BlueprintGraph.K2Node_MacroInstance'/Game/Blueprints/Pawn/BP_BasePawn.BP_BasePawn:EventGraph.K2Node_MacroInstance_1'"
   MacroGraphReference=(MacroGraph="/Script/Engine.EdGraph'/TouchInputSystem/Macros/TouchMacros.TouchMacros:TouchManager'",GraphBlueprint="/Script/Engine.Blueprint'/TouchInputSystem/Macros/TouchMacros.TouchMacros'",GraphGuid=6BC9C77246E079C4C3C47888685F151D)
   NodePosX=432
   NodePosY=-384
   NodeGuid=52A01E004D61CFECD0C9CB8FF3F95720
   CustomProperties Pin (PinId=E4FF9FC341533D603645888EF1D60F0E,PinName="Pressed",PinType.PinCategory="exec",PinType.PinSubCategory="",PinType.PinSubCategoryObject=None,PinType.PinSubCategoryMemberReference=(),PinType.PinValueType=(),PinType.ContainerType=None,PinType.bIsReference=False,PinType.bIsConst=False,PinType.bIsWeakPointer=False,PinType.bIsUObjectWrapper=False,PinType.bSerializeAsSinglePrecisionFloat=False,LinkedTo=(K2Node_InputTouch_0 71747E5C46A5053287FBAB8156E04742,),PersistentGuid=00000000000000000000000000000000,bHidden=False,bNotConnectable=False,bDefaultValueIsReadOnly=False,bDefaultValueIsIgnored=False,bAdvancedView=False,bOrphanedPin=False,)
   CustomProperties Pin (PinId=1F9BD817439970D5A565E4946D3E6936,PinName="Released",PinType.PinCategory="exec",PinType.PinSubCategory="",PinType.PinSubCategoryObject=None,PinType.PinSubCategoryMemberReference=(),PinType.PinValueType=(),PinType.ContainerType=None,PinType.bIsReference=False,PinType.bIsConst=False,PinType.bIsWeakPointer=False,PinType.bIsUObjectWrapper=False,PinType.bSerializeAsSinglePrecisionFloat=False,LinkedTo=(K2Node_InputTouch_0 D384F7C14BA527354AAE6293A732E556,),PersistentGuid=00000000000000000000000000000000,bHidden=False,bNotConnectable=False,bDefaultValueIsReadOnly=False,bDefaultValueIsIgnored=False,bAdvancedView=False,bOrphanedPin=False,)
   CustomProperties Pin (PinId=03130AA3464113E63F0AD789E24D9FD4,PinName="Moved",PinType.PinCategory="exec",PinType.PinSubCategory="",PinType.PinSubCategoryObject=None,PinType.PinSubCategoryMemberReference=(),PinType.PinValueType=(),PinType.ContainerType=None,PinType.bIsReference=False,PinType.bIsConst=False,PinType.bIsWeakPointer=False,PinType.bIsUObjectWrapper=False,PinType.bSerializeAsSinglePrecisionFloat=False,LinkedTo=(K2Node_InputTouch_0 186B088C45F42F513D5DBAAE614A8D08,),PersistentGuid=00000000000000000000000000000000,bHidden=False,bNotConnectable=False,bDefaultValueIsReadOnly=False,bDefaultValueIsIgnored=False,bAdvancedView=False,bOrphanedPin=False,)
   CustomProperties Pin (PinId=AEACB43B40F0E3FD69CCE391CAB09FA6,PinName="Location",PinType.PinCategory="struct",PinType.PinSubCategory="",PinType.PinSubCategoryObject="/Script/CoreUObject.ScriptStruct'/Script/CoreUObject.Vector'",PinType.PinSubCategoryMemberReference=(),PinType.PinValueType=(),PinType.ContainerType=None,PinType.bIsReference=False,PinType.bIsConst=False,PinType.bIsWeakPointer=False,PinType.bIsUObjectWrapper=False,PinType.bSerializeAsSinglePrecisionFloat=False,LinkedTo=(K2Node_InputTouch_0 B928E6764BB90A27B411A8825EFB863F,),PersistentGuid=00000000000000000000000000000000,bHidden=False,bNotConnectable=False,bDefaultValueIsReadOnly=False,bDefaultValueIsIgnored=False,bAdvancedView=False,bOrphanedPin=False,)
   CustomProperties Pin (PinId=0DB0546945E2A07E0453A7870CCB4BFE,PinName="FingerIndex",PinType.PinCategory="byte",PinType.PinSubCategory="",PinType.PinSubCategoryObject="/Script/CoreUObject.Enum'/Script/InputCore.ETouchIndex'",PinType.PinSubCategoryMemberReference=(),PinType.PinValueType=(),PinType.ContainerType=None,PinType.bIsReference=False,PinType.bIsConst=False,PinType.bIsWeakPointer=False,PinType.bIsUObjectWrapper=False,PinType.bSerializeAsSinglePrecisionFloat=False,DefaultValue="Touch1",AutogeneratedDefaultValue="Touch1",LinkedTo=(K2Node_InputTouch_0 6C193C104799BCCD7B82B6BCEAAA0D95,),PersistentGuid=00000000000000000000000000000000,bHidden=False,bNotConnectable=False,bDefaultValueIsReadOnly=False,bDefaultValueIsIgnored=False,bAdvancedView=False,bOrphanedPin=False,)
End Object</code></pre>
<button onclick="copyToClipboard()" style="position: absolute; top: 5px; right: 5px; padding: 5px 10px; background: #0366d6; color: white; border: none; border-radius: 3px; cursor: pointer;">
📋 Copy
</button>
</div>

<script>
function copyToClipboard() {
    const code = document.getElementById('code-block').textContent;
    navigator.clipboard.writeText(code).then(() => {
        event.target.textContent = '✅ Copied!';
        setTimeout(() => {
            event.target.textContent = '📋 Copy';
        }, 2000);
    });
}
</script>
