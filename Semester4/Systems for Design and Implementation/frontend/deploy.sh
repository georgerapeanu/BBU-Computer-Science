API_URL=$MANUAL_API_URL;
export API_URL;

for i in ./src/environments/*.tmpl;do 
    cat $i | envsubst > ${i%.*};
done; 

if [ -z $IS_PRODUCTION_BRANCH ] ; then
  ng build --configuration=development;
else 
  ng build --configuration=production;
fi
