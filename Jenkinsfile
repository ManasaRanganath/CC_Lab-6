pipeline {
    agent any
    stages {
        stage('Checkout SCM') {
            steps {
                checkout scm
            }
        }
        stage('Build Backend Image') {
            steps {
                sh 'docker build -t backend-app ./backend'
            }
        }
        stage('Deploy Backend Containers') {
            steps {
                sh 'docker rm -f backend1 backend2 || true'
                sh 'docker run -d --name backend1 --network cc-lab-net backend-app'
                sh 'docker run -d --name backend2 --network cc-lab-net backend-app'
                sleep 5
            }
        }
        stage('Deploy NGINX Load Balancer') {
            steps {
                sh 'docker rm -f nginx-lb || true'
                // Start NGINX on the shared network
                sh 'docker run -d --name nginx-lb --network cc-lab-net -p 80:80 nginx'
                sleep 3
                // Manually copy the config to avoid volume mount permission issues
                sh 'docker cp ./nginx/default.conf nginx-lb:/etc/nginx/conf.d/default.conf'
                // Reload NGINX to apply the configuration
                sh 'docker exec nginx-lb nginx -s reload'
                sleep 5
            }
        }
    }
    post {
        success {
            echo 'Pipeline executed successfully, NGINX load balancer is running.'
        }
        failure {
            echo 'Pipeline failed. Check console logs for errors.'
        }
    }
}