using UnityEngine;

public class BallController : MonoBehaviour
{
	public float force = 5;
	Rigidbody2D rb;

	void Awake()
	{
		rb = GetComponent<Rigidbody2D>();
	}

	void Start ()
	{
		rb.AddForce(new Vector2(1, 0.5f)* force);
	}
}
