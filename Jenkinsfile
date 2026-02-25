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
                sh 'docker run -d --name backend1 backend-app'
                sh 'docker run -d --name backend2 backend-app'
                sleep 5
            }
        }
        stage('Deploy NGINX Load Balancer') {
            steps {
                sh 'docker rm -f nginx-lb || true'
                // Mounting the directory to conf.d is the most stable method for this lab
                sh 'docker run -d --name nginx-lb -p 80:80 -v $(pwd)/nginx:/etc/nginx/conf.d:ro nginx'
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