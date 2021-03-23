
using UnityEngine;
using TMPro;

public class Break : MonoBehaviour
{
    public float health = 10f;
    public GameObject Trigger;
    public string MainDisplayText = "";
    public string SubDisplayText = "";
    public TextMeshProUGUI MainTextBox;
    public TextMeshProUGUI SubTextBox;
    public float timer = 3f;
    public bool displayed = false;


    public void TakeDamage(float Damage)
    {
        health -= Damage;
        if (health <= 0f)
        {
            if (Trigger != null)
            {
                Destroy(Trigger);
                MainTextBox.text = MainDisplayText;
                SubTextBox.text = SubDisplayText;
                displayed = true;
            }
            else
            {
                Destroy(gameObject);
            }
        }
    }
    void Update()
    {
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
                Destroy(gameObject);
            }
        }
    }
}
