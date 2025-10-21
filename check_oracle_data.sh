#!/bin/bash
# Check Oracle Database Data

echo "=========================================="
echo "   CHECKING ORACLE DATABASE DATA"
echo "=========================================="
echo ""

echo "📡 Connecting to Oracle Database..."
echo ""

# Check if table exists and show data
docker exec oracle-db sqlplus -s system/MyPassword123@XE << EOF
SET PAGESIZE 50
SET LINESIZE 200
SET FEEDBACK ON

-- Check if table exists
SELECT 'Checking if FOURNISSEURS table exists...' AS STATUS FROM DUAL;

SELECT COUNT(*) AS TABLE_EXISTS 
FROM user_tables 
WHERE table_name = 'FOURNISSEURS';

-- If table exists, show data
SELECT '---' AS SEPARATOR FROM DUAL;
SELECT 'FOURNISSEURS Table Data:' AS INFO FROM DUAL;
SELECT '---' AS SEPARATOR FROM DUAL;

SELECT 
    ID_FOURNISSEUR AS ID,
    NOM,
    EMAIL,
    TELEPHONE AS TEL,
    TYPE_PRODUITS AS TYPE
FROM FOURNISSEURS
WHERE ROWNUM <= 10;

SELECT '---' AS SEPARATOR FROM DUAL;
SELECT 'Total Records: ' || COUNT(*) AS TOTAL FROM FOURNISSEURS;

EXIT;
EOF

echo ""
echo "=========================================="
echo "           CHECK COMPLETE"
echo "=========================================="
echo ""
echo "💡 If you see 'TABLE_EXISTS = 0', the table doesn't exist yet."
echo "   This means your app is using JSON files (which is fine!)"
echo ""
echo "💡 If you see data above, it's in Oracle! ✅"
echo ""

