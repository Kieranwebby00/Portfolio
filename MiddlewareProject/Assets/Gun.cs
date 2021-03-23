
using UnityEngine;

public class Gun : MonoBehaviour
{
    public float damage = 1f;
    public float range = 100f;
    public GameObject Impact;
    public bool PickedUp = false;

    public Camera GunCamera;
    public ParticleSystem Flash;
    // Update is called once per frame
    void Update()
    {
        if (Input.GetButtonDown("Fire1"))
        {
            RaycastHit Bullet;
            if (Physics.Raycast(GunCamera.transform.position, GunCamera.transform.forward, out Bullet, range))
            {
                Flash.Play();
                Debug.Log(Bullet.transform.name);
                Break target = Bullet.transform.GetComponent<Break>();
                if (target != null)
                {
                    target.TakeDamage(damage);
                }
                GameObject Temp = Instantiate(Impact, Bullet.point, Quaternion.LookRotation(Bullet.normal));
                Destroy(Temp, 2f);
            }
        }
    }
}
