pipeline {
    agent any
    stages {
        stage('Checkout SCM') {
            steps {
                [cite_start]checkout scm [cite: 536-540]
            }
        }
        stage('Build Backend Image') {
            steps {
                [cite_start]// Building the C++ backend image [cite: 544-547]
                sh 'docker build -t backend-app ./backend'
            }
        }
        stage('Deploy Backend Containers') {
            steps {
                [cite_start]// Removing old backends and starting new ones on a shared network [cite: 341, 560]
                sh 'docker rm -f backend1 backend2 || true'
                [cite_start]sh 'docker run -d --name backend1 --network cc-lab-net backend-app' [cite: 343, 561]
                [cite_start]sh 'docker run -d --name backend2 --network cc-lab-net backend-app' [cite: 346]
                [cite_start]sleep 5 [cite: 749]
            }
        }
        stage('Deploy NGINX Load Balancer') {
            steps {
                [cite_start]// Running NGINX on the same network so it can resolve backend1 and backend2 [cite: 563-568]
                sh 'docker rm -f nginx-lb || true'
                [cite_start]sh 'docker run -d --name nginx-lb --network cc-lab-net -p 80:80 -v $(pwd)/nginx:/etc/nginx/conf.d:ro nginx' [cite: 482, 570]
                [cite_start]sleep 5 [cite: 750]
            }
        }
    }
    post {
        success {
            [cite_start]echo 'Pipeline executed successfully, NGINX load balancer is running.' [cite: 461]
        }
        failure {
            echo 'Pipeline failed. [cite_start]Check console logs for errors.' [cite: 738]
        }
    }
}