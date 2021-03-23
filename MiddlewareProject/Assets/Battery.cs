using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Battery : MonoBehaviour
{
    public Slider BatteryBar;
    public void SetBattery(float Value)
    {
        BatteryBar.value = Value;
    }
}
