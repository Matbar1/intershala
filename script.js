$(document).ready(function() {
    const clientData = {
      "clients": [
        {"isManager":true,"id":1,"label":"Client1"},
        {"isManager":false,"id":2,"label":"Client2"},
        {"isManager":false,"id":3,"label":"Client3"},
        {"isManager":false,"id":4,"label":"Client4"},
        {"isManager":false,"id":5,"label":"Client5"}
      ],
      "data": {
        "1": {"address":"NY","name":"Jhon","points":123},
        "2": {"address":"NY","name":"Dan","points":123},
        "3": {"address":"NY","name":"Ben","points":123}
      },
      "label": "All Clients"
    };
  
    const clientList = $('#client-list');
    const popup = $('#popup');
    const popupContent = $('#popup-content');
    const popupName = $('#popup-name');
    const popupPoints = $('#popup-points');
    const popupAddress = $('#popup-address');
  
    // Initialize doT template
    const clientItemTemplate = doT.template(`
      <li class="client-item">
        {{=it.label}} - {{=it.points}}
      </li>
    `);
  
    // Populate the client list and handle filtering
    function populateClientList(filter) {
      clientList.empty();
      clientData.clients.forEach(function(client) {
        if (filter === 'all' || (filter === 'managers' && client.isManager) || (filter === 'non-managers' && !client.isManager)) {
          const listItem = $(clientItemTemplate(client));
          listItem.click(function() {
            const clientDetails = clientData.data[client.id];
            popupName.text(clientDetails.name);
            popupPoints.text('Points: ' + clientDetails.points);
            popupAddress.text('Address: ' + clientDetails.address);
            popup.fadeIn();
          });
          clientList.append(listItem);
        }
      });
    }
  
    // Handle filter change
    $('#filter').change(function() {
      const selectedFilter = $(this).val();
      populateClientList(selectedFilter);
    });
  
    // Close popup on clicking outside
    $(document).click(function(event) {
      if (!$(event.target).closest('.popup-content').length) {
        popup.fadeOut();
      }
    });
  
    // Initial population of the client list
    populateClientList('all');
  });
  