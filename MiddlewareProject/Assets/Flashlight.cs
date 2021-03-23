
using UnityEngine;
using TMPro;


public class Flashlight : MonoBehaviour
{

    public Light F_light;
    public float Battery = 1f;
    public bool dead = false;
    public bool Start = true;
    public Battery F_Battery;
    public string MainDisplayText = "The flashlights battery is dead";
    public string SubDisplayText = "It must fully recharge before use.";
    public TextMeshProUGUI MainTextBox;
    public TextMeshProUGUI SubTextBox;
    public bool displayed = false;
    public float timer = 3f;

    // Update is called once per frame
    void Update()
    {
        //Debug.Log(Battery);
        //turns the light off on start
        if (Start)
        {
            F_light.enabled = false;
            Start = false;
        }

        //uses up the lights battery
        if (F_light.enabled)
        {
            Battery -= 0.001f;
            if (Battery <= 0)
            {
                dead = true;
                F_light.enabled = false;
                MainTextBox.text = MainDisplayText;
                SubTextBox.text = SubDisplayText;
                displayed = true;
            }
           else
            {
                dead = false;
            }
        }

        //dissables the light untill fully charged
        if (dead)
        {
            if ( Battery >= 1)
            {
                dead = false;
            }
        }

        //recharges the battery
        if (F_light.enabled == false)
        {
            if (Battery < 1)
            {
                Battery += 0.0005f;
            }
            
        }

        //toggles the light
        if (Input.GetKeyDown(KeyCode.F))
        {
            if (!dead)
            {
                if (F_light.enabled)
                {
                    F_light.enabled = false;
                }
                else
                {
                    F_light.enabled = true;
                }
            }
        }

        if (displayed)
        {
            if (timer > 0)
            {
                timer -= Time.deltaTime;
            }
            if (timer <= 0)
            {
                MainTextBox.text = " ";
                SubTextBox.text = " ";
                displayed = false;
            }
        }
        
        //updates the bar
        F_Battery.SetBattery(Battery);
    }
}
 