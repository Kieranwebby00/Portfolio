
using UnityEngine;
using TMPro;

public class Pickup : MonoBehaviour
{
    public string MainDisplayText = "Press E to pick up a Knife";
    public string MainDisplayText2 = "You have picked up a Knife";
    public string subDisplayText = "Press 1 to equip it.";
    public TextMeshProUGUI MainTextBox;
    public TextMeshProUGUI SubTextBox;
    public GameObject  WeaponType;
    public bool pickedup = false;

    private void OnTriggerStay(Collider other)
    {
        if (!pickedup)
        {
            if (other.CompareTag("Player"))
            {
                MainTextBox.text = MainDisplayText;
                SubTextBox.text = "";
                if (Input.GetKeyDown(KeyCode.E))
                {
                    WeaponType.GetComponent<Gun>().PickedUp = true;
                    pickedup = true;
                    MainTextBox.text = MainDisplayText2;
                    SubTextBox.text = subDisplayText;

                }
            }
        }
        
    }

    private void OnTriggerExit(Collider other)
    {
        MainTextBox.text = "";
        SubTextBox.text = "";
    }


}