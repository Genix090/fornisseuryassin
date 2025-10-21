#!/bin/bash
# 🚀 Oracle Database Setup Script
# Run this to install Oracle Database in Docker!

echo "🚀 Starting Oracle Database Setup..."
echo ""

# Check if Docker is running
if ! docker info > /dev/null 2>&1; then
    echo "❌ Docker is not running!"
    echo "Please start Docker Desktop first:"
    echo "   1. Open Applications → Docker"
    echo "   2. Wait for Docker icon in menu bar"
    echo "   3. Run this script again"
    exit 1
fi

echo "✅ Docker is running!"
echo ""

# Pull Oracle Database Express Edition
echo "📥 Downloading Oracle Database (this may take 5-10 minutes)..."
docker pull container-registry.oracle.com/database/express:21c

echo ""
echo "✅ Oracle Database image downloaded!"
echo ""

# Run Oracle Database
echo "🚀 Starting Oracle Database container..."
echo "   Container name: oracle-db"
echo "   Port: 1521"
echo "   Password: MyPassword123"
echo ""

docker run -d \
  --name oracle-db \
  -p 1521:1521 \
  -p 5500:5500 \
  -e ORACLE_PWD=MyPassword123 \
  container-registry.oracle.com/database/express:21c

echo ""
echo "✅ Oracle Database container started!"
echo ""
echo "⏳ Waiting for database to initialize (this takes 2-3 minutes)..."
echo "   You can watch the progress with: docker logs -f oracle-db"
echo ""

# Wait and check status
sleep 10

echo "📊 Checking database status..."
docker logs oracle-db | tail -20

echo ""
echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
echo "🎉 SETUP COMPLETE!"
echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
echo ""
echo "📝 CONNECTION DETAILS:"
echo "   Host:     localhost"
echo "   Port:     1521"
echo "   SID:      XE"
echo "   Username: system"
echo "   Password: MyPassword123"
echo ""
echo "⏳ Database is initializing... Wait for this message in logs:"
echo "   'DATABASE IS READY TO USE!'"
echo ""
echo "🔍 To check if database is ready, run:"
echo "   docker logs oracle-db | grep 'READY'"
echo ""
echo "🛑 To stop Oracle:"
echo "   docker stop oracle-db"
echo ""
echo "▶️  To start Oracle again:"
echo "   docker start oracle-db"
echo ""
echo "🗑️  To remove Oracle (if you want to start fresh):"
echo "   docker stop oracle-db && docker rm oracle-db"
echo ""
echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
echo ""
echo "✅ Now you can use Oracle in your Qt project!"
echo "   Use the oracleconnection.h class"
echo "   Connection: localhost:1521/XE"
echo ""
echo "🌟 Your teacher will be IMPRESSED!"
echo ""

