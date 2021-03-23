
using UnityEngine;
using TMPro;

public class TextPopup : MonoBehaviour
{
    public string MainDisplayText = "Press F to toggle light";
    public string SubDisplayText = "It will recharge when not in use.";
    public TextMeshProUGUI MainTextBox;
    public TextMeshProUGUI SubTextBox;
    public bool displayed = false;
    

    private void OnTriggerEnter(Collider other)
    {
        if (!displayed)
        {
            if (other.CompareTag("Player"))
            {
                MainTextBox.text = MainDisplayText;
                SubTextBox.text = SubDisplayText;
                displayed = true;
            }
        }
    }



    private void OnTriggerExit(Collider other)
    {
       MainTextBox.text = " ";
       SubTextBox.text = " ";
    }
}
