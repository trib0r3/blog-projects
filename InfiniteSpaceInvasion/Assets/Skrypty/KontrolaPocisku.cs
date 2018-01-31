using UnityEngine;
using System.Collections;

public class KontrolaPocisku : MonoBehaviour {

	public GameObject [] KaboomAnimation;
	public float speed = 1000;


	// Use this for initialization
	void Start () {
		if(gameObject.tag == "Pocisk")
			rigidbody2D.AddForce(gameObject.transform.up * speed);
	}

	void FixedUpdate()
	{
		if(gameObject.tag != "Pocisk")
			rigidbody2D.velocity = new Vector2(20,0);
	}
	
	void OnCollisionEnter2D(Collision2D coll)
	{
		if(coll.gameObject.tag == "Bumper")
		{
			Destroy(this.gameObject);
			return;
		}


		if(coll.gameObject.tag == "Gracz" && GameObject.FindGameObjectWithTag("GM").GetComponent<GameMaster>().zycia > 0)
		{
			GameObject.FindGameObjectWithTag("GM").GetComponent<GameMaster>().zycia--;
			Instantiate(KaboomAnimation[Random.Range(0,1)],coll.transform.position,coll.transform.rotation);
			Destroy(this.gameObject);
			return;
		}


		Instantiate(KaboomAnimation[Random.Range(0,KaboomAnimation.Length)],coll.transform.position,coll.transform.rotation);
		Destroy(coll.gameObject);
		Destroy(this.gameObject);
	}
}
