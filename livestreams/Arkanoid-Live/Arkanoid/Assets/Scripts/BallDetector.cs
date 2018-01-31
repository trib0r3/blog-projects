using UnityEngine;
using UnityEngine.SceneManagement;

public class BallDetector : MonoBehaviour
{
	void OnTriggerEnter2D(Collider2D other)
	{
		if(other.gameObject.CompareTag("Ball"))
		{
			SceneManager.LoadScene("main"); // zamiana! na live tu bylo 0
		}
	}
	
}
