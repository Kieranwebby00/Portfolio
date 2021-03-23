
using UnityEngine;

public class SwapWeapon : MonoBehaviour
{
    public int CurrentWeapon = 0;
    // Start is called before the first frame update

    // Update is called once per frame
    void Update()
    {
        if (Input.GetKeyDown(KeyCode.Alpha1))
        {
            CurrentWeapon = 0;
        }
        if (Input.GetKeyDown(KeyCode.Alpha2))
        {

            CurrentWeapon = 1;

        }
        int i = 0;
        foreach (Transform Weapons in transform)
        {
            if (i == CurrentWeapon)
            {
                Gun temp = Weapons.gameObject.GetComponent<Gun>();
                if (temp.PickedUp)
                {
                    Weapons.gameObject.SetActive(true);
                }
                else
                {
                    Weapons.gameObject.SetActive(false);
                }
                

            }
            else
            {
                Weapons.gameObject.SetActive(false);
            }
            i++;
        }
    }

}

