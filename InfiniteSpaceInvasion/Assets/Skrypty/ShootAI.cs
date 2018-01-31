using UnityEngine;
using System.Collections;

public class ShootAI : MonoBehaviour {

	public float firerate = 3;
	public LayerMask ToHit;
	
	public float TimeToFire = 0;
	
	Transform firePoint;
	public GameObject Pocisk;
	
	void Awake()
	{
		firePoint = transform;
	}

	void Start()
	{
		TimeToFire = Random.Range(0,0.9f);
	}
	
	void Update () 
	{
		if(firePoint == null)
			return;

		if(firerate == 0)
		{
			shoot();
		}
		else
		{
			if(Time.time > TimeToFire)
			{
				TimeToFire = Time.time + 1/firerate + 2;
				shoot();
			}
		}
	}
	
	void shoot()
	{
		if(GameObject.FindWithTag("GM").GetComponent <GameMaster>().dzwiek == 1)
			audio.Play ();

		Instantiate(Pocisk,transform.position,transform.rotation);
	}
}
