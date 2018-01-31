using UnityEngine;
using System.Collections;

public class Kontrolagracza : MonoBehaviour {

	public GameObject master;

	void Start()
	{
		if(master != null)
		{
			int t = master.GetComponent <GameMaster> ().dzwiek;

			audio.mute = (t == 0 ? true : false);
		}
	}


	void FixedUpdate () 
	{
		float move = Input.GetAxis("Vertical");

		rigidbody2D.velocity = new Vector2 (6,move*10);
	}


	void OnCollisionEnter2D(Collision2D coll)
	{
		audio.pitch = Random.Range(0.5f,0.9f);
		audio.Play();
	}
}
