package com.example.app.secrets;

/**
 * Utility class for managing the JWT secret.
 */
public class JWTSecretManager {

    /**
     * Retrieves the JWT secret from the environment variables.
     *
     * @return the JWT secret
     */
    public static String getSecret() {
        return System.getenv("JWT_SECRET");
    }
}
