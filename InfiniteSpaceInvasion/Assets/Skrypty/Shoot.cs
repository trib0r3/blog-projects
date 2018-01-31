using UnityEngine;
using System.Collections;

public class Shoot : MonoBehaviour {

	public float firerate = 0;				// czas pomiędzy wystrzałami
	public LayerMask ToHit;					// obiekty, które kolidują z graczem

	public float TimeToFire = 0;			// czas po którym gracz może strzelać
	public GameObject Bullet;				// typ wsytzeliwanych pocisków

	GameMaster master;						// wskaźnik na skrypt (ammo)
	

	void Awake()
	{	
		master = GameObject.FindWithTag("GM").GetComponent <GameMaster>();
	}

	void Update () 
	{
		if(firerate == 0)
		{
			if(Input.GetButtonDown("Fire1") && master.ammunition > 0)
			{
				shoot();
			}
		}
		else
		{
			if((Input.GetButton("Fire1")) && Time.time > TimeToFire && master.ammunition > 0)
			{
				TimeToFire = Time.time + 1/firerate;
				shoot();
			}
		}
	}

	void shoot()
	{
		if(master.dzwiek == 1)
			audio.Play();

		Instantiate(Bullet,transform.position,transform.rotation);
		master.ammunition-=1;
	}
}
